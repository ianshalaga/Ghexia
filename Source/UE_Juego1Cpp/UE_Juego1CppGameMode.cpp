// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_Juego1CppGameMode.h"
#include "UE_Juego1CppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE_Juego1CppGameMode::AUE_Juego1CppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
