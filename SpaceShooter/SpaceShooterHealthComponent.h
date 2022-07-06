// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceShooterHealthComponent.generated.h"


class ASpaceShooterPlayerState;
class USpaceShooterPlayerDmgUserWidget;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE5LAB_API USpaceShooterHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpaceShooterHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void TakeDamage(float Damage);
	float GetCurrentHealth() const;
	bool IsDead() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float InitHealth;
protected:

	TWeakObjectPtr<ASpaceShooterPlayerState> State;
	UPROPERTY(EditAnywhere)
		TSubclassOf<USpaceShooterPlayerDmgUserWidget> DamageWidget;
	UPROPERTY()
	USpaceShooterPlayerDmgUserWidget* DamageUI;


};
