// Fill out your copyright notice in the Description page of Project Settings.
#include "SpaceShooterObstacleLevel.h"
#include "SpaceShooterObstacle.h"
#include "SpaceShooterPlayerController.h"
#include "Ue5Lab/Utilities/Logger.h"

bool USpaceShooterObstacleLevel::IsLevelFinish()
{
	return ObstacleSettings.IsEmpty() && SettingInitCount <= SettingCount && !IsSettingExist && AliveObstacle.IsEmpty();
}

bool USpaceShooterObstacleLevel::IsLevelPlaying()
{
	return IsTicking;
}

void USpaceShooterObstacleLevel::OnObstacleDestroy(ASpaceShooterObstacle* SpaceShooterObstacle)
{
	AliveObstacle.Remove(SpaceShooterObstacle);
}

void USpaceShooterObstacleLevel::StartLevel(const FVector Origin, const FVector BoxExtend)
{
	Logger::Log(FString::Printf(TEXT("New Level:%s has being start"), *LevelName));

	OnObstacleDestroyHandle = FSpaceShooterObstacleEvents::OnObstacleDestroy.AddUObject(this, &USpaceShooterObstacleLevel::OnObstacleDestroy);
	IsTicking = true;
	SpawnOrigin = Origin;
	SpawnBoxExtend = BoxExtend;
	SettingInitCount = ObstacleSettings.Num();
	SettingCount = 0;
	IsSettingExist = false;
	AliveObstacle.Empty();

}

void USpaceShooterObstacleLevel::StopLevel()
{
	IsTicking = false;
	FSpaceShooterObstacleEvents::OnObstacleDestroy.Remove(OnObstacleDestroyHandle);
}

void USpaceShooterObstacleLevel::TickLevel(float Delta)
{
	if (!IsTicking) {
		return;
	}
	Elapsed += Delta;
	//當存在當前設定的時候
	if (IsSettingExist) {
		//已超過設定的存活時間
		if (CurrentSetting.ElapsedTime <= SettingElapsed) {
			SettingCount++;
			IsSettingExist = false;
		}
		//到達下一次的生成時間
		else if (SettingElapsed >= NextSpawnTime) {
			for (int i = 0; i < NextAmount; i++)
			{
				SpawnObstacle();
			}
			UpdateSpawnTimeAndAmount();
		}
		SettingElapsed += Delta;
	}

	//如果現在沒有設定存在嘗試找一個新的設定
	if (!IsSettingExist) {
		if (!ObstacleSettings.IsEmpty()) {
			FSpaceShooterObstacleSetting Setting = ObstacleSettings.Pop();
			CurrentSetting = Setting;
			SettingElapsed = 0.0f;
			IsSettingExist = true;
			UpdateSpawnTimeAndAmount();
		}
		else if (AliveObstacle.IsEmpty())
		{
			OnLevelFinish.Broadcast(this);
			IsTicking = false;
		}
	}
}

void USpaceShooterObstacleLevel::SpawnObstacle()
{
	FVector SpawnOffset = FVector(FMath::RandRange(-SpawnBoxExtend.X, SpawnBoxExtend.X),
		FMath::RandRange(-SpawnBoxExtend.Y, SpawnBoxExtend.Y),
		FMath::RandRange(-SpawnBoxExtend.Z, SpawnBoxExtend.Z));
	FVector SpawnPos = SpawnOrigin + SpawnOffset;
	UWorld* World = GetWorld();
	if (World) {
		ASpaceShooterObstacle* Obstacle = World->SpawnActor<ASpaceShooterObstacle>(CurrentSetting.Obstacle, SpawnPos, FRotator::ZeroRotator);
		AliveObstacle.Emplace(Obstacle);
	}
}

void USpaceShooterObstacleLevel::UpdateSpawnTimeAndAmount()
{
	NextSpawnTime = SettingElapsed + FMath::RandRange(CurrentSetting.IntervalMin, CurrentSetting.IntervalMax);
	NextSpawnTime = FMath::Clamp(NextSpawnTime, 0.0f, CurrentSetting.ElapsedTime);
	NextAmount = FMath::RandRange(CurrentSetting.AmountMin, CurrentSetting.AmountMax);
}
