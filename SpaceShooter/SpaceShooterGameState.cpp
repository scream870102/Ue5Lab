// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterGameState.h"

ASpaceShooterGameState::ASpaceShooterGameState()
{
	ResetScore();
}

int ASpaceShooterGameState::GetScore() const
{
	return Score;
}

void ASpaceShooterGameState::AddScore(int Plus)
{
	Score += Plus;
}

void ASpaceShooterGameState::ResetScore()
{
	Score = 0;
}
