// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SpaceShooterGameState.generated.h"

/**
 *
 */
UCLASS()
class UE5LAB_API ASpaceShooterGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ASpaceShooterGameState();
public:
	int GetScore() const;
	void AddScore(int Plus);
	void ResetScore();
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		int Score;
};
