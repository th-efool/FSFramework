// Fill out your copyright notice in the Description page of Project Settings.


#include "Brokers/FSWorldBroker.h"

#include "Components/WidgetInteractionComponent.h"
#include "Match/FSMatchGameFrameworkBroker.h"
#include "Match/FSMatchUIBroker.h"

void UFSWorldBroker::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (UFSMatchGameFrameworkBroker*FrameworkBroker =GetGameFrameworkBroker(GetWorld()))
	{
			FrameworkBroker->OnPlayerJoined.AddDynamic(this, &UFSWorldBroker::HandlePlayerJoined);
			FrameworkBroker->OnPlayerLeft.AddDynamic(this, &UFSWorldBroker::HandlePlayerLeft);
	}
	if (UFSMatchUIBroker* MatchUIBroker =GetUIBroker(GetWorld()))
	{
		
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

void UFSWorldBroker::HandleSanityChanged(float Percent)
{
	OnSanityChanged.Broadcast(Percent);

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUISanityChanged.Broadcast(Percent);
	}
}

void UFSWorldBroker::HandleHealthChanged(float Percent)
{
	OnHealthChanged.Broadcast(Percent);

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUIHealthChanged.Broadcast(Percent);
	}
}

void UFSWorldBroker::HandleAnnouncement(const FText& Msg, float Time)
{
	OnAnnouncement.Broadcast(Msg, Time);

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUIAnnouncement.Broadcast(Msg, Time);
	}
}

void UFSWorldBroker::HandleSubtitle(const FText& Msg, float Time)
{
	OnSubtitle.Broadcast(Msg, Time);

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUISubtitle.Broadcast(Msg, Time);
	}
}

void UFSWorldBroker::HandleDiaryShow(const FText& Date, const FText& Body)
{
	OnDiaryShow.Broadcast(Date, Body);

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUIDiaryShow.Broadcast(Date, Body);
	}
}

void UFSWorldBroker::HandleDiaryHide()
{
	OnDiaryHide.Broadcast();

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUIDiaryHide.Broadcast();
	}
}
