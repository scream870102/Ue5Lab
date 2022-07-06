// Fill out your copyright notice in the Description page of Project Settings.
#include "SpaceShooterObstacle.h"
#include "SpaceShooterConst.h"
#include "SpaceShooterPlayer.h"
#include "SpaceShooterHealthBarUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Ue5Lab/Utilities/Logger.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

FSpaceShooterObstacleEvents::FOnObstacleExplode FSpaceShooterObstacleEvents::OnObstacleExplode;
FSpaceShooterObstacleEvents::FOnObstacleDestroy FSpaceShooterObstacleEvents::OnObstacleDestroy;
// Sets default values
ASpaceShooterObstacle::ASpaceShooterObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(SpaceShooterConst::ObstacleTag);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
}

// Called when the game starts or when spawned
void ASpaceShooterObstacle::BeginPlay()
{
	Super::BeginPlay();
	if (!Collision) {
		Collision = FindComponentByClass<UPrimitiveComponent>();
	}
	if (!ExplosionFx) {
		ExplosionFx = FindComponentByClass<UParticleSystemComponent>();
	}
	if (ExplosionFx) {
		ExplosionFx->Deactivate();
	}

	CurrentHealth = InitialHealth;
	SetVelocity();
	VelocityCache = ProjectileMovementComponent->Velocity;
	Collision->OnComponentHit.AddDynamic(this, &ASpaceShooterObstacle::OnHit);

	HealthUI = CreateWidget<USpaceShooterHealthBarUserWidget>(GetWorld(), HPWidget);
	HealthUI->AddToViewport();


	float X = FMath::RandRange(RotationVelocityMin, RotationVelocityMax);
	float Y = FMath::RandRange(RotationVelocityMin, RotationVelocityMax);
	float Z = FMath::RandRange(RotationVelocityMin, RotationVelocityMax);
	PerRotation = FRotator(X, Y, Z);

	SetLifeSpan(LifeTime);
}

void ASpaceShooterObstacle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	HealthUI->RemoveFromParent();
	FSpaceShooterObstacleEvents::OnObstacleDestroy.Broadcast(this);
	Super::EndPlay(EndPlayReason);
}

void ASpaceShooterObstacle::SetVelocity(FVector NewVel) const
{
	if (NewVel == FVector::ZeroVector)
	{
		const float X = FMath::RandRange(InitialSpeedRangeMin.X, InitialSpeedRangeMax.X);
		const float Y = FMath::RandRange(InitialSpeedRangeMin.Y, InitialSpeedRangeMax.Y);
		const float Z = FMath::RandRange(InitialSpeedRangeMin.Z, InitialSpeedRangeMax.Z);
		NewVel = FVector(X, Y, Z);
	}
	ProjectileMovementComponent->Velocity = NewVel;
}

void ASpaceShooterObstacle::PendingDestroy()
{
	if (ExplosionFx) {
		ExplosionFx->Activate(true);
	}
	FSpaceShooterObstacleEvents::OnObstacleExplode.Broadcast(this);
	if (Renderer)
	{
		Renderer->Deactivate();
	}
	FTimerHandle DestroyDelayHandler;
	GetWorldTimerManager().SetTimer(DestroyDelayHandler, [&]()
		{
			Destroy();
		}, ExplosionFxElapsed, false);
}

bool ASpaceShooterObstacle::ShouldBeDestroy() const
{
	return CurrentHealth <= 0.0f;
}

void ASpaceShooterObstacle::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor->Implements<USpaceShooterHitAble>() && OtherActor->ActorHasTag(SpaceShooterConst::PlayerTag)) {
		ISpaceShooterHitAble* HitAble = Cast<ISpaceShooterHitAble>(OtherActor);
		HitAble->Hit(Damage, this);
		//TODO: Play Explosion Fx
	}
	else if (OtherComp->GetCollisionObjectType() == SpaceShooterConst::ProjectileChannel)
	{
		return;
	}
	Destroy();
}

// Called every frame
void ASpaceShooterObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ProjectileMovementComponent->Velocity != VelocityCache || LocationCache == GetActorLocation())
	{
		SetVelocity(VelocityCache);
	}
	LocationCache = GetActorLocation();

	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (FVector2D ViewportLocation;  UGameplayStatics::ProjectWorldToScreen(PlayerController, GetActorLocation(), ViewportLocation))
	{
		HealthUI->SetPositionInViewport(ViewportLocation);
	}

	AddActorLocalRotation(PerRotation * DeltaTime);

}

void ASpaceShooterObstacle::Hit(const float BeHitDamage, AActor* Other)
{
	CurrentHealth -= BeHitDamage;
	HealthUI->SetValue(CurrentHealth / InitialHealth);
	if (ShouldBeDestroy()) {
		PendingDestroy();
	}
}

