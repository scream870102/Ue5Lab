// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterWeaponContainer.h"

#include "SpaceShooterConst.h"
#include "SpaceShooterPlayer.h"
#include "Ue5Lab/Utilities/Logger.h"

// Sets default values
ASpaceShooterWeaponContainer::ASpaceShooterWeaponContainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASpaceShooterWeaponContainer::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(SpaceShooterConst::PlayerTag))
	{
		ASpaceShooterPlayer* Player = Cast<ASpaceShooterPlayer>(OtherActor);
		Player->GetWeapon(Weapon);
		Destroy();
	}
}

// Called when the game starts or when spawned
void ASpaceShooterWeaponContainer::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ASpaceShooterWeaponContainer::OnBeginOverlap);

}

// Called every frame
void ASpaceShooterWeaponContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

