// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/Components/FSTeamStatusPanel.h"

#include "Match/FSMatchUIBroker.h"
#include "Utility/FSErrorHandler.h"

void UFSTeamStatusPanel::AddPlayerEntry(const FString& Name, const FString& ID, UTexture2D* Avatar)
{
	if (!PlayerListBox || !PlayerEntryClass)
	{
		return;
	}

	UFSTeamStatusPanelEntry* NewEntry = CreateWidget<UFSTeamStatusPanelEntry>(GetWorld(), PlayerEntryClass);


	if (!NewEntry)
	{
		return;
	}

	NewEntry->InitializeEntry(Name, ID, Avatar);

	PlayerListBox->AddChildToVerticalBox(NewEntry);
}


void UFSTeamStatusPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (UWorld* World = GetWorld())
	{
		if (UFSMatchUIBroker* UIBroker = World->GetSubsystem<UFSMatchUIBroker>())
		{
			// Bind once — Blueprint-safe dynamic delegate
			UIBroker->OnUIPlayerJoined.AddDynamic(this, &UFSTeamStatusPanel::HandlePlayerJoined);
			UIBroker->OnUIPlayerLeft.AddDynamic(this, &UFSTeamStatusPanel::HandlePlayerLeft);
		}
	}

}

void UFSTeamStatusPanel::NativeDestruct()
{
	Super::NativeDestruct();
	if (UWorld* World = GetWorld())
	{
		if (UFSMatchUIBroker* UIBroker = World->GetSubsystem<UFSMatchUIBroker>())
		{
			UIBroker->OnUIPlayerJoined.RemoveDynamic(this, &UFSTeamStatusPanel::HandlePlayerJoined);
			UIBroker->OnUIPlayerLeft.RemoveDynamic(this, &UFSTeamStatusPanel::HandlePlayerLeft);
		}
	}
}

void UFSTeamStatusPanel::HandlePlayerJoined(const FPlayerJoinInfo& Info)
{
	const FString PlayerName = Info.PlayerState->GetPlayerName();
	
	/*
	const FString PlayerID = Info.PlayerState->GetUniqueId().IsValid()
		? Info.PlayerState->GetUniqueId()->ToString()
		: FString::FromInt(Info.PlayerState->GetPlayerId());
	*/
	const FString PlayerID = FString::FromInt(Info.PlayerState->GetPlayerId());
	
	AddPlayerEntry(PlayerName, PlayerID, nullptr);
}

void UFSTeamStatusPanel::HandlePlayerLeft(APlayerState* PlayerState)
{
	
}
