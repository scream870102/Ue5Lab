// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterPlayerState.h"

#include "Ue5Lab/Utilities/Logger.h"

float ASpaceShooterPlayerState::GetHealth() const
{
	return CurrentHealth;
}

void ASpaceShooterPlayerState::SetHealth(const float NewHealth)
{
	CurrentHealth = NewHealth;
}

float ASpaceShooterPlayerState::GetCurrentHealth()
{
	return CurrentHealth;
}
