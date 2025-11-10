// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/FSMainMenuWidget.h"
#include "Menu/FSMenuUIBroker.h"
#include "Utility/FSErrorHandler.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UFSMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ======== Bind Buttons ========
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

	// ======== Bind Broker Callbacks ========
	if (UWorld* World = GetWorld())
	{
		if (UFSMenuUIBroker* UIBroker = World->GetSubsystem<UFSMenuUIBroker>())
		{
			UIBroker->OnLoginComplete.AddDynamic(this, &UFSMainMenuWidget::HandleLoginResult);
			UIBroker->OnDevAuthComplete.AddDynamic(this, &UFSMainMenuWidget::HandleDevAuthResult);
		}
	}

	// Initialize UI
	UpdateUIState();
}

void UFSMainMenuWidget::UpdateUIState()
{
	bool bLogged = false;
	FString PlayerName = TEXT("Guest");

	FS_PRINT_SCREEN(TEXT("UpdateUIState() called"));

	if (UWorld* World = GetWorld())
	{
		if (UFSMenuUIBroker* UIBroker = World->GetSubsystem<UFSMenuUIBroker>())
		{
			UIBroker->GetLoginStatus(bLogged);
			UIBroker->GetPlayerName(PlayerName);

			FS_PRINT_SCREEN(*FString::Printf(
				TEXT("UIBroker found → LoginStatus=%s | PlayerName=%s"),
				bLogged ? TEXT("true") : TEXT("false"),
				*PlayerName));
		}
		else
		{
			FS_PRINT_SCREEN(TEXT("⚠️ UFSMenuUIBroker subsystem not found"));
		}
	}
	else
	{
		FS_PRINT_SCREEN(TEXT("❌ GetWorld() returned null"));
	}

	bIsLoggedIn = bLogged;
	CachedPlayerName = PlayerName;

	// === Username ===
	if (UsernameText)
	{
		UsernameText->SetText(FText::FromString(CachedPlayerName));
		FS_PRINT_SCREEN(*FString::Printf(TEXT("UsernameText updated → %s"), *CachedPlayerName));
	}
	else
	{
		FS_PRINT_SCREEN(TEXT("⚠️ UsernameText not bound"));
	}

	// === Multiplayer ===
	if (MultiplayerButton)
	{
		MultiplayerButton->SetIsEnabled(bIsLoggedIn);
		FS_PRINT_SCREEN(*FString::Printf(TEXT("MultiplayerButton → %s"),
			bIsLoggedIn ? TEXT("ENABLED") : TEXT("DISABLED")));
	}
	else
	{
		FS_PRINT_SCREEN(TEXT("⚠️ MultiplayerButton not bound"));
	}

	// === LoginWithEOS ===
	if (LoginWithEOSButton)
	{
		LoginWithEOSButton->SetVisibility(bIsLoggedIn ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
		LoginWithEOSButton->SetIsEnabled(!bIsLoggedIn);

		FS_PRINT_SCREEN(*FString::Printf(TEXT("LoginWithEOSButton → %s / %s"),
			bIsLoggedIn ? TEXT("HIDDEN") : TEXT("VISIBLE"),
			bIsLoggedIn ? TEXT("DISABLED") : TEXT("ENABLED")));
	}
	else
	{
		FS_PRINT_SCREEN(TEXT("⚠️ LoginWithEOSButton not bound"));
	}

	// === LoginDev ===
	if (LoginDevButton)
	{
		LoginDevButton->SetVisibility(bIsLoggedIn ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
		LoginDevButton->SetIsEnabled(!bIsLoggedIn);

		FS_PRINT_SCREEN(*FString::Printf(TEXT("LoginDevButton → %s / %s"),
			bIsLoggedIn ? TEXT("HIDDEN") : TEXT("VISIBLE"),
			bIsLoggedIn ? TEXT("DISABLED") : TEXT("ENABLED")));
	}
	else
	{
		FS_PRINT_SCREEN(TEXT("⚠️ LoginDevButton not bound"));
	}

	// === Summary ===
	FS_PRINT_SCREEN(*FString::Printf(
		TEXT("✅ UpdateUIState complete → LoggedIn=%s | Username=%s | Buttons=%s"),
		bIsLoggedIn ? TEXT("true") : TEXT("false"),
		*CachedPlayerName,
		bIsLoggedIn ? TEXT("HIDDEN") : TEXT("VISIBLE")));
}


// =======================================================================
// ==================== BUTTON CALLBACKS =================================
// =======================================================================

void UFSMainMenuWidget::OnPlaySoloClicked()
{
	FS_INFO_MSG(nullptr, *FString::Printf(TEXT("OnPlaySoloClicked → Solo play triggered")));
	// TODO: Start single-player session
}

void UFSMainMenuWidget::OnMultiplayerClicked()
{
	if (!bIsLoggedIn)
	{
		FS_ERROR_MSG( nullptr, *FString::Printf(TEXT("Multiplayer clicked but user not logged in — ignoring")));
		return;
	}

	FS_INFO_MSG(nullptr, *FString::Printf(TEXT("OnMultiplayerClicked → Launching multiplayer for %s"), *CachedPlayerName));
	// TODO: Open multiplayer lobby/session
}

void UFSMainMenuWidget::OnSettingsClicked()
{
	FS_INFO_MSG(nullptr, *FString::Printf(TEXT("OnSettingsClicked → Opening settings")));
	// TODO: Open settings menu
}

void UFSMainMenuWidget::OnLoginWithEOSClicked()
{
	FS_INFO_MSG(nullptr, *FString::Printf(TEXT("OnLoginWithEOSClicked → Requesting EOS login")));

	if (UWorld* World = GetWorld())
	{
		if (UFSMenuUIBroker* UIBroker = World->GetSubsystem<UFSMenuUIBroker>())
		{
			UIBroker->Login(TEXT(""), TEXT(""), TEXT("accountportal"));
		}
	}
}

void UFSMainMenuWidget::OnLoginDevClicked()
{
	FS_INFO_MSG(nullptr, *FString::Printf(TEXT("OnLoginDevClicked → Requesting DevAuth login")));

	if (UWorld* World = GetWorld())
	{
		if (UFSMenuUIBroker* UIBroker = World->GetSubsystem<UFSMenuUIBroker>())
		{
			UIBroker->DevAuth();
		}
	}
}

// =======================================================================
// ==================== LOGIN RESULT CALLBACKS ============================
// =======================================================================

void UFSMainMenuWidget::HandleLoginResult(bool bSuccess, const FString& Error)
{
	if (bSuccess)
	{
		FS_SHOW_POPUP(*FString::Printf(TEXT("HandleLoginResult → EOS Login succeeded")));
	}
	else
	{
		FS_SHOW_POPUP(*FString::Printf(TEXT("HandleLoginResult → EOS Login failed: %s"), *Error));
	}

	UpdateUIState();
}

void UFSMainMenuWidget::HandleDevAuthResult(bool bSuccess, const FString& Error)
{
	if (bSuccess)
	{
		FS_SHOW_POPUP(*FString::Printf(TEXT("HandleDevAuthResult → DevAuth Login succeeded")));
	}
	else
	{
		
		FS_PRINT_SCREEN(*FString::Printf(TEXT("HandleDevAuthResult → DevAuth Login failed: %s"), *Error));
	}

	UpdateUIState();
}
