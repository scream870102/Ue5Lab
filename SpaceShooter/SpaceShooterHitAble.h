// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpaceShooterHitAble.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpaceShooterHitAble : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class UE5LAB_API ISpaceShooterHitAble
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Hit(const float Damage, AActor* From) = 0;
};
