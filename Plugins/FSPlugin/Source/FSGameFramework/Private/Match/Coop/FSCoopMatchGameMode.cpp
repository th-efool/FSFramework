// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/Coop/FSCoopMatchGameMode.h"

#include "Match/Coop/FSCoopMatchGameState.h"
#include "Match/Coop/FSCoopMatchPlayerController.h"
#include "Match/Coop/FSCoopMatchPlayerState.h"

AFSCoopMatchGameMode::AFSCoopMatchGameMode()
{
	PlayerControllerClass = AFSCoopMatchPlayerController::StaticClass();
	GameStateClass        = AFSCoopMatchGameState::StaticClass();
	PlayerStateClass      = AFSCoopMatchPlayerState::StaticClass();
}
