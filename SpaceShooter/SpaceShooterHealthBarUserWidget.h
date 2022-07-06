// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpaceShooterHealthBarUserWidget.generated.h"

/**
 *
 */

class UProgressBar;
UCLASS()
class UE5LAB_API USpaceShooterHealthBarUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USpaceShooterHealthBarUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual  void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
		void SetValue(float Value);
protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* HitAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HealthBar;
};
