// Fill out your copyright notice in the Description page of Project Settings.


#include "Brokers/FSWorldBroker.h"

#include "Match/FSMatchGameFrameworkBroker.h"
#include "Match/FSMatchUIBroker.h"

void UFSWorldBroker::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (UWorld* World = GetWorld())
	{
		if (UFSMatchGameFrameworkBroker* FrameworkBroker = World->GetSubsystem<UFSMatchGameFrameworkBroker>())
		{
			FrameworkBroker->OnPlayerJoined.AddDynamic(this, &UFSWorldBroker::HandlePlayerJoined);
			FrameworkBroker->OnPlayerLeft.AddDynamic(this, &UFSWorldBroker::HandlePlayerLeft);
		}
	}
	
}

void UFSWorldBroker::Deinitialize()
{
	Super::Deinitialize();
	
}

void UFSWorldBroker::HandlePlayerJoined(const FPlayerJoinInfo& Info)
{
	OnPlayerJoined.Broadcast(Info);

	if (UWorld* World = GetWorld())
	{
		if (UFSMatchUIBroker* UIBroker = World->GetSubsystem<UFSMatchUIBroker>())
		{
			UIBroker->OnUIPlayerJoined.Broadcast(Info);
		}
	}
	
		
}

void UFSWorldBroker::HandlePlayerLeft(APlayerState* PS)
{
	OnPlayerLeft.Broadcast(PS);
	if (UWorld* World = GetWorld())
	{
		if (UFSMatchUIBroker* UIBroker = World->GetSubsystem<UFSMatchUIBroker>())
		{
			UIBroker->OnUIPlayerLeft.Broadcast(PS);
		}
	}
}
