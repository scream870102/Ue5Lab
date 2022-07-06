// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpaceShooterPlayer.h"
#include "SpaceShooterPlayerController.generated.h"

/**
 *
 */
class UUserWidget;

UCLASS()
class UE5LAB_API ASpaceShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HealthWidget;
	UPROPERTY()
	UUserWidget* HealthUI;
	virtual  void OnLevelStart();

private:
	UPROPERTY()
		ASpaceShooterPlayer* SpacePlayerRef;
public:
	virtual void PostInitializeComponents() override;
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlayingState() override;
private:
	void MoveForwardImpl(float Axis);
	void MoveRightImpl(float Axis);
	void StartFiringImpl();
	void StopFiringImpl();

};
