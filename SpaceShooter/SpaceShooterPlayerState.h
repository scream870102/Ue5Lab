// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SpaceShooterPlayerState.generated.h"

/**
 *
 */
UCLASS()
class UE5LAB_API ASpaceShooterPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	float GetHealth() const;
	void SetHealth(float NewHealth);

	UFUNCTION(BlueprintCallable)
		float GetCurrentHealth();
protected:
	UPROPERTY(EditAnywhere)
		float CurrentHealth;
};
