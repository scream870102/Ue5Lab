// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"

void USpaceShooterGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &USpaceShooterGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &USpaceShooterGameInstance::EndLoadingScreen);
}

void USpaceShooterGameInstance::BeginLoadingScreen(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreen;

	LoadingWidget = CreateWidget<UUserWidget>(this, LoadingWidgetClass);
	const TSharedPtr<SWidget> WidgetPtr = LoadingWidget->TakeWidget();
	LoadingScreen.WidgetLoadingScreen = WidgetPtr;
	LoadingScreen.MinimumLoadingScreenDisplayTime = 1.0f;

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);

}

void USpaceShooterGameInstance::EndLoadingScreen(UWorld* LoadedWorld)
{
	if (LoadingWidget)
	{
		LoadingWidget->RemoveFromParent();
		LoadingWidget->MarkAsGarbage();
	}
}
