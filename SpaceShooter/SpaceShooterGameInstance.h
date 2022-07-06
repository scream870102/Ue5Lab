// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpaceShooterGameInstance.generated.h"

/**
 *
 */
class UUserWidget;
UCLASS()
class UE5LAB_API USpaceShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);

	UFUNCTION()
		virtual void EndLoadingScreen(UWorld* LoadedWorld);


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, FString> DataContainer;
protected:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> LoadingWidgetClass;

	UPROPERTY()
		UUserWidget* LoadingWidget;



};
