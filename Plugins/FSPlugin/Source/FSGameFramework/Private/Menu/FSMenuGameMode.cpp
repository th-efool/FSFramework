// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/FSMenuGameMode.h"

#include "Menu/FSMenuGameState.h"
#include "Menu/FSMenuPlayerController.h"
#include "Menu/FSMenuPlayerState.h"

AFSMenuGameMode::AFSMenuGameMode()
{
	PlayerControllerClass = AFSMenuPlayerController::StaticClass();
	GameStateClass        = AFSMenuGameState::StaticClass();
	PlayerStateClass      = AFSMenuPlayerState::StaticClass();

}
