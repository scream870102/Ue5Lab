// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterHealthComponent.h"

#include "SpaceShooterPlayer.h"
#include "SpaceShooterPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "SpaceShooterPlayerDmgUserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpaceShooterHealthComponent::USpaceShooterHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void USpaceShooterHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	if (const ASpaceShooterPlayer* Parent = Cast<ASpaceShooterPlayer>(GetOwner()))
	{
		if (ASpaceShooterPlayerState* CastState = Cast<ASpaceShooterPlayerState>(Parent->GetPlayerState()))
		{
			State = CastState;
			State->SetHealth(InitHealth);
		}
		DamageUI = CreateWidget<USpaceShooterPlayerDmgUserWidget>(GetWorld(), DamageWidget);

	}

}


// Called every frame
void USpaceShooterHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpaceShooterHealthComponent::TakeDamage(const float Damage)
{
	if (!State.IsValid())
	{
		return;
	}
	const float NewHealth = State->GetHealth() - Damage;
	State->SetHealth(NewHealth);

	DamageUI->SetValue(Damage);
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (FVector2D ViewportLocation;  UGameplayStatics::ProjectWorldToScreen(PlayerController, GetOwner()->GetActorLocation(), ViewportLocation))
	{
		DamageUI->SetPositionInViewport(ViewportLocation);
	}
	if (!DamageUI->IsInViewport())
	{
		DamageUI->AddToViewport();
	}

}

float USpaceShooterHealthComponent::GetCurrentHealth() const
{
	if (State.IsValid())
	{
		return State->GetHealth();
	}
	return 0;
}

bool USpaceShooterHealthComponent::IsDead() const
{
	if (State.IsValid())
	{
		return  State->GetHealth() <= 0.0f;
	}
	return  true;
}
