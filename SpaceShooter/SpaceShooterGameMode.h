// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceShooterGameMode.generated.h"

class ASpaceShooterObstacle;
class ASpaceShooterGameState;
class UUserWidget;
/**
 *
 */
UCLASS()
class UE5LAB_API ASpaceShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpaceShooterGameMode();
	virtual  void StartPlay() override;

protected:

	TWeakObjectPtr<ASpaceShooterGameState> GameState;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> ScoreWidget;
private:
	void OnObstacleExplode(const ASpaceShooterObstacle* Obstacle) const;
	void OnLevelStart();
	void EndGame() const;
	void OnLevelAllFinish() const;
	void OnPlayerDead() const;

	UPROPERTY()
	UUserWidget* ScoreUI;
};

class FSpaceShooterGameModeEvents
{
public:
	DECLARE_EVENT(ASpaceShooterGameMode,FOnGameEnd)
	static FOnGameEnd OnGameEnd;
};
