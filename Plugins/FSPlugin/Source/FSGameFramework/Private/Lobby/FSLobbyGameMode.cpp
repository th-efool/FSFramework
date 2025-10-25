// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/FSLobbyGameMode.h"

#include "Lobby/FSLobbyPlayerController.h"
#include "Lobby/FSLobbyGameState.h"
#include "Lobby/FSLobbyPlayerState.h"

AFSLobbyGameMode::AFSLobbyGameMode()
{
	PlayerControllerClass = AFSLobbyPlayerController::StaticClass();
	GameStateClass        = AFSLobbyGameState::StaticClass();
	PlayerStateClass      = AFSLobbyPlayerState::StaticClass();
}
