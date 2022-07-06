// Copyright Epic Games, Inc. All Rights Reserved.

#include "Ue5LabGameMode.h"
#include "Ue5LabCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUe5LabGameMode::AUe5LabGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
