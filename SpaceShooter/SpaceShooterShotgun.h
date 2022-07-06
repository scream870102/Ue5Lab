// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceShooterWeapon.h"
#include "SpaceShooterShotgun.generated.h"

/**
 *
 */
UCLASS()
class UE5LAB_API ASpaceShooterShotgun : public ASpaceShooterWeapon
{
	GENERATED_BODY()
public:
	virtual  void Firing() override;
protected:
	UPROPERTY(EditAnywhere, Category = "Shotgun")
		int BulletsPerShoot;
	UPROPERTY(EditAnywhere, Category = "Shotgun")
		float ShootRangeRadiusInDegree;
};
