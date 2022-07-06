// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpaceShooterObstacleLevel.generated.h"

class ASpaceShooterObstacle;
USTRUCT(BlueprintType)
struct FSpaceShooterObstacleSetting
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ASpaceShooterObstacle> Obstacle;
	UPROPERTY(EditAnywhere)
		float IntervalMin;
	UPROPERTY(EditAnywhere)
		float IntervalMax;
	UPROPERTY(EditAnywhere)
		int AmountMin;
	UPROPERTY(EditAnywhere)
		int AmountMax;
	UPROPERTY(EditAnywhere)
		float ElapsedTime;


};

class USpaceShooterObstacleLevel;
DECLARE_EVENT_OneParam(USpaceShooterObstacleLevel, FOnLevelFinish, const USpaceShooterObstacleLevel* Level)
/**
 *
 */
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class UE5LAB_API USpaceShooterObstacleLevel : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Level")
		FString LevelName;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		TArray<FSpaceShooterObstacleSetting> ObstacleSettings;

private:
	TArray<ASpaceShooterObstacle*> AliveObstacle;
	FSpaceShooterObstacleSetting CurrentSetting;
	FOnLevelFinish OnLevelFinish;
	bool IsTicking = false;
	float Elapsed = 0.0f;
	float SettingElapsed = 0.0f;
	float NextSpawnTime;
	int NextAmount;
	FVector SpawnOrigin;
	FVector SpawnBoxExtend;
	bool IsSettingExist = false;
	int SettingInitCount;
	int SettingCount;
	FDelegateHandle OnObstacleDestroyHandle;


public:
	bool IsLevelFinish();
	bool IsLevelPlaying();
	void OnObstacleDestroy(ASpaceShooterObstacle* SpaceShooterObstacle);
	void StartLevel(const FVector SpawnOrigin, const FVector SpawnBoxExtend);
	void StopLevel();
	void TickLevel(float Delta);

	void SpawnObstacle();

	void UpdateSpawnTimeAndAmount();


};


