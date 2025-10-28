// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/FSMatchGameFrameworkBroker.h"

void UFSMatchGameFrameworkBroker::NotifyPlayerJoined(APlayerController* PC)
{
	if (!PC || !PC->PlayerState) return;
	FPlayerJoinInfo Info { PC->PlayerState, PC->IsLocalController() };
	OnPlayerJoined.Broadcast(Info);

}

void UFSMatchGameFrameworkBroker::NotifyPlayerLeft(APlayerState* PS)
{
	if (!PS) return;
	OnPlayerLeft.Broadcast(PS);

}
