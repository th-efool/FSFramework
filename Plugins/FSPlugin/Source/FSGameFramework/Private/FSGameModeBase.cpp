// Fill out your copyright notice in the Description page of Project Settings.


#include "FSGameModeBase.h"

#include "FSGameStateBase.h"
#include "FSPlayerControllerBase.h"
#include "FSPlayerStateBase.h"

AFSGameModeBase::AFSGameModeBase()
{
	PlayerControllerClass = AFSPlayerControllerBase::StaticClass();
	GameStateClass        = AFSGameStateBase::StaticClass();
	PlayerStateClass      = AFSPlayerStateBase::StaticClass();
}
