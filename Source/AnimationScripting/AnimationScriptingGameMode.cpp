// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimationScriptingGameMode.h"
#include "AnimationScriptingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAnimationScriptingGameMode::AAnimationScriptingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
