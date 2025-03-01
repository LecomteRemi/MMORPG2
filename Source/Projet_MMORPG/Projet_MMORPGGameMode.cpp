// Copyright Epic Games, Inc. All Rights Reserved.

#include "Projet_MMORPGGameMode.h"
#include "PlayerPawn.h"
#include "UObject/ConstructorHelpers.h"

AProjet_MMORPGGameMode::AProjet_MMORPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_PlayerPawn"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
