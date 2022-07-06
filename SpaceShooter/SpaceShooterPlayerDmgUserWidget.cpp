// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterPlayerDmgUserWidget.h"

#include "Components/TextBlock.h"
#include "Ue5Lab/Utilities/Logger.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "DefaultNameSpace"

USpaceShooterPlayerDmgUserWidget::USpaceShooterPlayerDmgUserWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
}

void USpaceShooterPlayerDmgUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OnMoveAnimFinDelegate.BindDynamic(this, &USpaceShooterPlayerDmgUserWidget::OnMoveAnimFin);
	BindToAnimationFinished(MoveAnimation, OnMoveAnimFinDelegate);
}

void USpaceShooterPlayerDmgUserWidget::SetValue(float Value, bool IsPlayAnim)
{
	TextBox->SetText(FText::Format(LOCTEXT("Battle", "-{0}"), Value));
	if (IsPlayAnim)
	{
		PlayAnimation(MoveAnimation);
	}
}

void USpaceShooterPlayerDmgUserWidget::OnMoveAnimFin()
{
	RemoveFromViewport();
}
#undef LOCTEXT_NAMESPACE    
