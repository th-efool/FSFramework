// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/FSMainMenuWidget.h"

#include "Menu/UFSMenuUIBroker.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/FSErrorHandler.h"

void UFSMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ======== Bind Button Callbacks ========
	if (PlaySoloButton)
		PlaySoloButton->OnClicked.AddDynamic(this, &UFSMainMenuWidget::OnPlaySoloClicked);

	if (MultiplayerButton)
		MultiplayerButton->OnClicked.AddDynamic(this, &UFSMainMenuWidget::OnMultiplayerClicked);

	if (SettingsButton)
		SettingsButton->OnClicked.AddDynamic(this, &UFSMainMenuWidget::OnSettingsClicked);

	if (LoginWithEOSButton)
		LoginWithEOSButton->OnClicked.AddDynamic(this, &UFSMainMenuWidget::OnLoginWithEOSClicked);

	if (LoginDevButton)
		LoginDevButton->OnClicked.AddDynamic(this, &UFSMainMenuWidget::OnLoginDevClicked);

	// ======== Initialize EOS state ========
	UpdateUIState();

	
}

void UFSMainMenuWidget::UpdateUIState()
{
	if (!UsernameText) return;

	bool bLogged = false;
	FString PlayerName = TEXT("Guest");

	if (UWorld* World = GetWorld())
	{
		if (UUFSMenuUIBroker* UIBroker = World->GetSubsystem<UUFSMenuUIBroker>())
		{
			// Query current login state
			UIBroker->GetLoginStatus(bLogged);
			UIBroker->GetPlayerName(PlayerName);
		}
	}

	bIsLoggedIn = bLogged;

	UsernameText->SetText(FText::FromString(PlayerName));

	// Enable/disable buttons based on login state
	if (LoginWithEOSButton)
		LoginWithEOSButton->SetIsEnabled(!bIsLoggedIn);

	if (LoginDevButton)
		LoginDevButton->SetIsEnabled(!bIsLoggedIn);
}

void UFSMainMenuWidget::OnPlaySoloClicked()
{
	FS_INFO(FString("OnPlaySoloClicked → Solo play triggered"));
	// TODO: Implement solo session start logic
}

void UFSMainMenuWidget::OnMultiplayerClicked()
{
	FS_INFO(FString("OnMultiplayerClicked → Multiplayer session triggered"));
	// TODO: Implement multiplayer session logic
}

void UFSMainMenuWidget::OnSettingsClicked()
{
	FS_INFO(FString("OnSettingsClicked → Opening settings"));
	// TODO: Open settings UI
}

void UFSMainMenuWidget::OnLoginWithEOSClicked()
{
	FS_INFO(FString("OnLoginWithEOSClicked → Triggering EOS login"));

	if (UWorld* World = GetWorld())
	{
		if (UUFSMenuUIBroker* UIBroker = World->GetSubsystem<UUFSMenuUIBroker>())
		{
			const FString ID = TEXT("example_id");
			const FString Token = TEXT("example_token");
			const FString LoginType = TEXT("accountportal");
			UIBroker->Login(ID, Token, LoginType);
		}
	}
}

void UFSMainMenuWidget::OnLoginDevClicked()
{
	FS_INFO(FString("OnLoginDevClicked → Triggering DevAuth login"));

	if (UWorld* World = GetWorld())
	{
		if (UUFSMenuUIBroker* UIBroker = World->GetSubsystem<UUFSMenuUIBroker>())
		{
			UIBroker->DevAuth();
		}
	}
}

void UFSMainMenuWidget::OnEOSLoginStatusChanged(bool bLoggedIn)
{
	bIsLoggedIn = bLoggedIn;
	UpdateUIState();

	FS_INFO(*FString::Printf(TEXT("OnEOSLoginStatusChanged → LoggedIn=%s"), bLoggedIn ? TEXT("true") : TEXT("false")));
}

