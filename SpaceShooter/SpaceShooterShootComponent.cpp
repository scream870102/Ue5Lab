// Fill out your copyright notice in the Description page of Project Settings.

//#include "Utilities/Logger.h";
#include "SpaceShooterShootComponent.h"
#include "SpaceShooterProjectile.h"
#include "SpaceShooterWeapon.h"
#include "Ue5Lab/Utilities/Logger.h"

// Sets default values for this component's properties
USpaceShooterShootComponent::USpaceShooterShootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpaceShooterShootComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeapon = GetWorld()->SpawnActor<ASpaceShooterWeapon>(DefaultWeaponBP);
	if (CurrentWeapon) {
		CurrentWeapon->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		CurrentWeapon->Init(this);
	}
}


// Called every frame
void USpaceShooterShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USpaceShooterShootComponent::StartFiring()
{
	if (CurrentWeapon) {
		CurrentWeapon->StartFiring();
	}
}

void USpaceShooterShootComponent::StopFiring()
{
	if (CurrentWeapon) {
		CurrentWeapon->StopFiring();
	}
}

void USpaceShooterShootComponent::ChangeWeapon(TSubclassOf<ASpaceShooterWeapon> NewWeapon)
{
	if(CurrentWeapon)
	{
		CurrentWeapon->Disarm();
	}
	CurrentWeapon = GetWorld()->SpawnActor<ASpaceShooterWeapon>(NewWeapon);
	if (CurrentWeapon) {
		CurrentWeapon->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		CurrentWeapon->Init(this);
	}
}

