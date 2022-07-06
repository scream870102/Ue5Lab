// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterPlayerController.h"

#include "SpaceShooterObstacleManager.h"
#include "Blueprint/UserWidget.h"

void ASpaceShooterPlayerController::OnLevelStart()
{
	if (!HealthUI)
	{
		HealthUI = CreateWidget<UUserWidget>(this, HealthWidget);
		HealthUI->AddToViewport();
	}
}

void ASpaceShooterPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	FSpaceShooterObstacleManagerEvents::OnLevelStart.AddUObject(this, &ASpaceShooterPlayerController::OnLevelStart);
}

void ASpaceShooterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("Move Forward / Backward", this, &ASpaceShooterPlayerController::MoveForwardImpl);
	InputComponent->BindAxis("Move Right / Left", this, &ASpaceShooterPlayerController::MoveRightImpl);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ASpaceShooterPlayerController::StartFiringImpl);
	InputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ASpaceShooterPlayerController::StopFiringImpl);
}

void ASpaceShooterPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();
	SpacePlayerRef = Cast<ASpaceShooterPlayer>(GetPawn());
}

void ASpaceShooterPlayerController::MoveForwardImpl(float Axis)
{
	if (SpacePlayerRef) {
		SpacePlayerRef->MoveForward(Axis);
	}
}

void ASpaceShooterPlayerController::MoveRightImpl(float Axis)
{
	if (SpacePlayerRef) {
		SpacePlayerRef->MoveRight(Axis);
	}
}

void ASpaceShooterPlayerController::StartFiringImpl()
{
	if (SpacePlayerRef) {
		SpacePlayerRef->StartFiring();
	}
}

void ASpaceShooterPlayerController::StopFiringImpl()
{
	if (SpacePlayerRef) {
		SpacePlayerRef->StopFiring();
	}
}
