// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class UE5LAB_API SpaceShooterConst
{
public:
#pragma region TAG
	const static FName ObstacleTag;
	const static FName PlayerTag;
#pragma endregion

#pragma region COLLISION CHANNEL
	const static int ProjectileChannel;
#pragma endregion

#pragma region DATA CONTANINER KEY
	const static FString ScoreKey;
#pragma endregion DATA CONTAINER KEY

#pragma region LEVEL
	const static FName ResultLevel;
#pragma endregion LEVEL

public:
	SpaceShooterConst();
	~SpaceShooterConst();


};
