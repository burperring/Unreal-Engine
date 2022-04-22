// Copyright Epic Games, Inc. All Rights Reserved.

#include "DESTRUCTIBLE_MESH_16GameMode.h"
#include "DESTRUCTIBLE_MESH_16Character.h"
#include "UObject/ConstructorHelpers.h"

ADESTRUCTIBLE_MESH_16GameMode::ADESTRUCTIBLE_MESH_16GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
