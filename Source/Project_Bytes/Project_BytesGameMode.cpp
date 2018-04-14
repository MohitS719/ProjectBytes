// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Project_BytesGameMode.h"
#include "Project_BytesHUD.h"
#include "Project_BytesCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_BytesGameMode::AProject_BytesGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Characters/Exterminator/Behaviour/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProject_BytesHUD::StaticClass();
}
