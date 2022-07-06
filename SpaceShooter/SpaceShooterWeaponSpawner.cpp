// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterWeaponSpawner.h"

#include "SpaceShooterObstacleManager.h"
#include "SpaceShooterWeaponContainer.h"
#include "Ue5Lab/Utilities/Logger.h"

// Sets default values
ASpaceShooterWeaponSpawner::ASpaceShooterWeaponSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASpaceShooterWeaponSpawner::OnLevelStart()
{
	if (CurrentContainer)
	{
		CurrentContainer->Destroy();
		CurrentContainer = nullptr;
	}
	int index = FMath::RandRange(0, WeaponContainerTemplates.Num() - 1);
	TSubclassOf<ASpaceShooterWeaponContainer> container = WeaponContainerTemplates[index];
	while (container == LastSpawn)
	{
		index = FMath::RandRange(0, WeaponContainerTemplates.Num() - 1);
		container = WeaponContainerTemplates[index];
	}
	LastSpawn = container;
	AActor* anchor = SpawnAnchor[FMath::RandRange(0, SpawnAnchor.Num() - 1)];
	if (ASpaceShooterWeaponContainer* spawnedObj = GetWorld()->SpawnActor<ASpaceShooterWeaponContainer>(container, anchor->GetActorLocation(), FRotator::ZeroRotator))
	{
		CurrentContainer = spawnedObj;
	}
}

// Called when the game starts or when spawned
void ASpaceShooterWeaponSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceShooterWeaponSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	FSpaceShooterObstacleManagerEvents::OnLevelStart.Remove(OnLevelStartDelegateHandle);
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ASpaceShooterWeaponSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpaceShooterWeaponSpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnLevelStartDelegateHandle = FSpaceShooterObstacleManagerEvents::OnLevelStart.AddUObject(this, &ASpaceShooterWeaponSpawner::OnLevelStart);
}

