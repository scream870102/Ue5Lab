// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterObstacleManager.h"

#include "Ue5Lab/Utilities/Logger.h"

FSpaceShooterObstacleManagerEvents::FOnLevelAllFinish FSpaceShooterObstacleManagerEvents::OnLevelAllFinish;
FSpaceShooterObstacleManagerEvents::FOnLevelStart FSpaceShooterObstacleManagerEvents::OnLevelStart;
// Sets default values
ASpaceShooterObstacleManager::ASpaceShooterObstacleManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpaceShooterObstacleManager::BeginPlay()
{
	Super::BeginPlay();
	if (!CurrentLevel) {
		if (TryGetNewLevel()) {
			FSpaceShooterObstacleManagerEvents::OnLevelStart.Broadcast();
			CurrentLevel->StartLevel(SpawnOrigin, SpawnBoxExtend);
		}
	}
}

bool ASpaceShooterObstacleManager::TryGetNewLevel()
{
	if (!Levels.IsEmpty()) {
		CurrentLevel = Levels.Pop();
		return true;
	}
	return false;
}

// Called every frame
void ASpaceShooterObstacleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!CurrentLevel) {
		return;
	}
	USpaceShooterObstacleLevel* const Level = CurrentLevel;
	Level->TickLevel(DeltaTime);
	if (Level->IsLevelFinish()) {
		Level->StopLevel();
		if (TryGetNewLevel()) {
			FSpaceShooterObstacleManagerEvents::OnLevelStart.Broadcast();
			CurrentLevel->StartLevel(SpawnOrigin, SpawnBoxExtend);
		}
		else {
			CurrentLevel = nullptr;
			if (Levels.IsEmpty())
			{
				FSpaceShooterObstacleManagerEvents::OnLevelAllFinish.Broadcast();
			}
		}
	}
}