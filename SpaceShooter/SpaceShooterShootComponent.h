// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpaceShooterShootComponent.generated.h"

class ASpaceShooterWeapon;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE5LAB_API USpaceShooterShootComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpaceShooterShootComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartFiring();
	void StopFiring();

	void ChangeWeapon(TSubclassOf<ASpaceShooterWeapon> NewWeapon);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

protected:
	
private:
	UPROPERTY()
		ASpaceShooterWeapon* CurrentWeapon;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ASpaceShooterWeapon> DefaultWeaponBP;

};
