// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterGameMode.h"

#include "SpaceShooterConst.h"
#include "SpaceShooterGameInstance.h"
#include "SpaceShooterGameState.h"
#include "SpaceShooterObstacle.h"
#include "SpaceShooterObstacleManager.h"
#include "SpaceShooterPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Ue5Lab/Utilities/Logger.h"

FSpaceShooterGameModeEvents::FOnGameEnd FSpaceShooterGameModeEvents::OnGameEnd;

ASpaceShooterGameMode::ASpaceShooterGameMode()
{
}

void ASpaceShooterGameMode::StartPlay()
{
	FSpaceShooterObstacleEvents::OnObstacleExplode.AddUObject(this, &ASpaceShooterGameMode::OnObstacleExplode);
	FSpaceShooterObstacleManagerEvents::OnLevelStart.AddUObject(this, &ASpaceShooterGameMode::OnLevelStart);
	FSpaceShooterObstacleManagerEvents::OnLevelAllFinish.AddUObject(this, &ASpaceShooterGameMode::OnLevelAllFinish);
	FSpaceShooterPlayerEvents::OnPlayerDead.AddUObject(this, &ASpaceShooterGameMode::OnPlayerDead);
	Super::StartPlay();
	GameState = GetGameState<ASpaceShooterGameState>();
}

void ASpaceShooterGameMode::OnObstacleExplode(const ASpaceShooterObstacle* Obstacle) const
{
	if (GameState.IsValid())
	{
		GameState->AddScore(1);
	}
}

void ASpaceShooterGameMode::OnLevelStart()
{
	Logger::Error(FString::Printf(TEXT("%sLevel Start"), *GetName()));
	if (!ScoreUI)
	{
		ScoreUI = CreateWidget<UUserWidget>(GetWorld(), ScoreWidget);
		ScoreUI->AddToViewport();
	}
}

void ASpaceShooterGameMode::EndGame() const
{
	USpaceShooterGameInstance* Instance = Cast<USpaceShooterGameInstance>(GetGameInstance());
	Instance->DataContainer.Add(SpaceShooterConst::ScoreKey, FString::FromInt(GameState->GetScore()));
	FSpaceShooterGameModeEvents::OnGameEnd.Broadcast();
	UGameplayStatics::OpenLevel(this, SpaceShooterConst::ResultLevel);
}

void ASpaceShooterGameMode::OnLevelAllFinish() const
{
	Logger::Error(FString(TEXT("Level Finish")));
	EndGame();
}

void ASpaceShooterGameMode::OnPlayerDead() const
{
	Logger::Error(FString(TEXT("Player Dead")));
	EndGame();
}
