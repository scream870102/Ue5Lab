// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterPlayer.h"

#include "SpaceShooterConst.h"
#include "SpaceShooterObstacleManager.h"
#include "Blueprint/UserWidget.h"
#include "Ue5Lab/Utilities/Logger.h"

FSpaceShooterPlayerEvents::FOnPlayerDead FSpaceShooterPlayerEvents::OnPlayerDead;
// Sets default values
ASpaceShooterPlayer::ASpaceShooterPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(SpaceShooterConst::PlayerTag);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ParticleSystems = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ExplosionFx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionFX"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	DeathExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathExplosionSound"));

	ShipMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleSystems->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionFx->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	DeathExplosionSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MaxVelocity = 250.0f;
	CurrentXVelocity = 0.0f;
	CurrentYVelocity = 0.0f;

	ShootComponent = CreateDefaultSubobject<USpaceShooterShootComponent>(TEXT("ShootComponent"));
	HealthComponent = CreateDefaultSubobject<USpaceShooterHealthComponent>(TEXT("HealthComponent"));
	ShootComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}

void ASpaceShooterPlayer::MoveRight(float Axis)
{
	CurrentXVelocity = MaxVelocity * Axis;
}

void ASpaceShooterPlayer::MoveForward(float Axis)
{
	CurrentYVelocity = MaxVelocity * Axis * -1.0f;
}

//TODO: Handle BeginOverlap to check if being hit or touch with pickable item
void ASpaceShooterPlayer::OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor)
{
}

void ASpaceShooterPlayer::CollectablePickup()
{
}

void ASpaceShooterPlayer::StartFiring() const
{
	ShootComponent->StartFiring();
}

void ASpaceShooterPlayer::StopFiring() const
{
	ShootComponent->StopFiring();
}

void ASpaceShooterPlayer::Hit(const float Damage, AActor* From)
{
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(Damage);
		if (HealthComponent->IsDead())
		{
			FSpaceShooterPlayerEvents::OnPlayerDead.Broadcast();
			Destroy();
		}
	}
}

void ASpaceShooterPlayer::GetWeapon(TSubclassOf<ASpaceShooterWeapon> NewWeaponBP) const
{
	if (ShootComponent)
	{
		ShootComponent->ChangeWeapon(NewWeaponBP);
	}
}

// Called when the game starts or when spawned
void ASpaceShooterPlayer::BeginPlay()
{
	Super::BeginPlay();
	CurrentLocation = this->GetActorLocation();
	CurrentRotation = this->GetActorRotation();

	bDead = false;
	bHit = false;

	ExplosionFx->Deactivate();
	DeathExplosionSound->Deactivate();

	OnActorBeginOverlap.AddDynamic(this, &ASpaceShooterPlayer::OnBeginOverlap);

	//Init Value here
	this->SetActorScale3D(InitScale);
}

void ASpaceShooterPlayer::UpdateRotation()
{
	if (CurrentYVelocity > 0.1f)
	{
		this->SetActorRotation(FRotator(CurrentRotation.Pitch - 45.0f, CurrentRotation.Yaw, CurrentRotation.Roll));
	}
	else if (CurrentYVelocity < -0.1f)
	{
		this->SetActorRotation(FRotator(CurrentRotation.Pitch + 45.0f, CurrentRotation.Yaw, CurrentRotation.Roll));
	}
	else
	{
		this->SetActorRotation(FRotator(CurrentRotation));
	}
}

void ASpaceShooterPlayer::FixLocationIfNeeded()
{
	if (this->GetActorLocation().X > FieldWidth) {
		CurrentLocation = FVector(FieldWidth - 1.0f, CurrentLocation.Y, CurrentLocation.Z);
	}
	else if (this->GetActorLocation().X < -FieldWidth) {
		CurrentLocation = FVector(-FieldWidth + 1.0f, CurrentLocation.Y, CurrentLocation.Z);
	}

	if (this->GetActorLocation().Y > FieldHeight) {
		CurrentLocation = FVector(CurrentLocation.X, FieldHeight - 1.0f, CurrentLocation.Z);
	}
	else if (this->GetActorLocation().Y < -FieldHeight) {
		CurrentLocation = FVector(CurrentLocation.X, -FieldHeight + 1.0f, CurrentLocation.Z);
	}
}

void ASpaceShooterPlayer::UpdateLocation(float DeltaTime)
{
	if (CurrentXVelocity != 0.0f || CurrentYVelocity != 0.0f) {
		NewLocation = FVector(CurrentLocation.X + (CurrentXVelocity * DeltaTime), CurrentLocation.Y + (CurrentYVelocity * DeltaTime), 0.0f);
		this->SetActorLocation(NewLocation);
		CurrentLocation = NewLocation;
	}
}

// Called every frame
void ASpaceShooterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocation(DeltaTime);
	UpdateRotation();
	FixLocationIfNeeded();
}

// Called to bind functionality to input
void ASpaceShooterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

