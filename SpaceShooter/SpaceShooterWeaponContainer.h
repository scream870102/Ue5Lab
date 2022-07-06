// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceShooterWeaponContainer.generated.h"

class ASpaceShooterWeapon;
UCLASS()
class UE5LAB_API ASpaceShooterWeaponContainer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpaceShooterWeaponContainer();

protected:
	UFUNCTION()
		void OnBeginOverlap(AActor* Actor, AActor* Actor1);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ASpaceShooterWeapon> Weapon;

};
