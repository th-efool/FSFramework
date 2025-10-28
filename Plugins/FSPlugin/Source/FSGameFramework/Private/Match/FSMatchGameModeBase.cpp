// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/FSMatchGameModeBase.h"

#include "Match/FSMatchGameStateBase.h"
#include "Match/FSMatchPlayerControllerBase.h"
#include "Match/FSMatchPlayerStateBase.h"

AFSMatchGameModeBase::AFSMatchGameModeBase()
{
	PlayerControllerClass = AFSMatchPlayerControllerBase::StaticClass();
	GameStateClass = AFSMatchGameStateBase::StaticClass();
	PlayerStateClass = AFSMatchPlayerStateBase::StaticClass();
}
