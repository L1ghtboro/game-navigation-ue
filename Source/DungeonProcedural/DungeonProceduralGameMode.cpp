// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonProceduralGameMode.h"
#include "DungeonProceduralCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADungeonProceduralGameMode::ADungeonProceduralGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
