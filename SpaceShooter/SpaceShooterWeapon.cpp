// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterWeapon.h"
#include "SpaceShooterProjectile.h"
#include "SpaceShooterShootComponent.h"
#include "Ue5Lab/Utilities/Logger.h"

// Sets default values
ASpaceShooterWeapon::ASpaceShooterWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASpaceShooterWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceShooterWeapon::SpawnProjectile(const FVector ShootDir)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	if (const auto Projectile = GetWorld()->SpawnActor<ASpaceShooterProjectile>(WeaponProjectileBP, ShootComponent->GetComponentLocation(), FRotator::ZeroRotator, SpawnParams)) {
		Projectile->Fire(ShootDir);
	}
}

// Called every frame
void ASpaceShooterWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ASpaceShooterWeapon::IsWeaponHasParent()
{
	return HasParent;
}

bool ASpaceShooterWeapon::IsFiring()
{
	return IsFire;
}

void ASpaceShooterWeapon::Init(USpaceShooterShootComponent* Parent)
{
	this->ShootComponent = Parent;
	HasParent = true;
}

void ASpaceShooterWeapon::Disarm()
{
	IsFire = false;
	GetWorldTimerManager().ClearTimer(FireTimerHandler);
}

void ASpaceShooterWeapon::StartFiring()
{
	IsFire = true;
	GetWorldTimerManager().SetTimer(FireTimerHandler, this, &ASpaceShooterWeapon::Firing, FireRate, true);
}

void ASpaceShooterWeapon::StopFiring()
{
	Disarm();
}

void ASpaceShooterWeapon::Firing()
{
	SpawnProjectile(ShootComponent->GetForwardVector());
}

