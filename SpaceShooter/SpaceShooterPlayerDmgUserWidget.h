// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpaceShooterPlayerDmgUserWidget.generated.h"

/**
 *
 */
class UWidgetAnimation;
class UTextBlock;
class FWidgetAnimationDynamicEvent;
UCLASS()
class UE5LAB_API USpaceShooterPlayerDmgUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	USpaceShooterPlayerDmgUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual  void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
		void SetValue(float Value, bool IsPlayAnim = true);
protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* MoveAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextBox;
private:
	FWidgetAnimationDynamicEvent OnMoveAnimFinDelegate;

	UFUNCTION()
		void OnMoveAnimFin();

};
