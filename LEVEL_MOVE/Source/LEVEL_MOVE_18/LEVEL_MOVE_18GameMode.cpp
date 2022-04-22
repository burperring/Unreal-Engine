// Copyright Epic Games, Inc. All Rights Reserved.

#include "LEVEL_MOVE_18GameMode.h"
#include "LEVEL_MOVE_18Character.h"
#include "UObject/ConstructorHelpers.h"

ALEVEL_MOVE_18GameMode::ALEVEL_MOVE_18GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
