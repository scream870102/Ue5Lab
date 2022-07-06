// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterProjectile.h"
#include "SpaceShooterObstacle.h"
#include "SpaceShooterConst.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ue5Lab/Utilities/Logger.h"

// Sets default values
ASpaceShooterProjectile::ASpaceShooterProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = CollisionComponent;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	InitialLifeSpan = LifeSpan;
}

// Called when the game starts or when spawned
void ASpaceShooterProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASpaceShooterProjectile::OnHit);
}

void ASpaceShooterProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->Implements<USpaceShooterHitAble>() && OtherActor->ActorHasTag(SpaceShooterConst::ObstacleTag)) {
		ISpaceShooterHitAble* HitAble = Cast<ISpaceShooterHitAble>(OtherActor);
		HitAble->Hit(Damage, this);
		Destroy();
	}
}

// Called every frame
void ASpaceShooterProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpaceShooterProjectile::Fire(const FVector& FireDir)
{
	ProjectileMovementComponent->Velocity = FireDir * ProjectileMovementComponent->InitialSpeed;
}

