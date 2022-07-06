// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterHealthBarUserWidget.h"

#include "Components/ProgressBar.h"

USpaceShooterHealthBarUserWidget::USpaceShooterHealthBarUserWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
}

void USpaceShooterHealthBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USpaceShooterHealthBarUserWidget::SetValue(float Value)
{
	HealthBar->SetPercent(Value);
	PlayAnimation(HitAnimation);
}
