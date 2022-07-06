// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceShooterObstacleLevel.h"
#include "SpaceShooterObstacleManager.generated.h"

UCLASS()
class UE5LAB_API ASpaceShooterObstacleManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpaceShooterObstacleManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool TryGetNewLevel();

public:
protected:
	UPROPERTY(EditAnywhere, Category = "Level")
		TArray<USpaceShooterObstacleLevel*> Levels;
	UPROPERTY(EditAnywhere, Category = "Level")
		FVector SpawnOrigin;
	UPROPERTY(EditAnywhere, Category = "Level")
		FVector SpawnBoxExtend;

	UPROPERTY()
	USpaceShooterObstacleLevel* CurrentLevel;
};

class FSpaceShooterObstacleManagerEvents
{
public:
	DECLARE_EVENT(ASpaceShooterObstacleManager, FOnLevelAllFinish)
	DECLARE_EVENT(ASpaceShooterObstacleManager, FOnLevelStart)
	static FOnLevelAllFinish OnLevelAllFinish;
	static FOnLevelStart OnLevelStart;
};
