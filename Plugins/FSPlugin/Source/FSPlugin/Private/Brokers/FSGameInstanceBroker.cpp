#include "Brokers/FSGameInstanceBroker.h"
#include "Menu/FSMenuUIBroker.h"
#include "Menu/FSMenuGameFrameworkBroker.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Utility/FSErrorHandler.h"

void UFSGameInstanceBroker::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (UWorld* World = GetGameInstance()->GetWorld())
	{
		FTimerHandle DeferredHandle;
		World->GetTimerManager().SetTimer(
			DeferredHandle,
			this,
			&UFSGameInstanceBroker::PerformDeferredBinding,
			1.0f,
			false
		);
		FS_INFO(FString("UFSGameInstanceBroker::Initialize → Deferred binding scheduled"));
	}
}

void UFSGameInstanceBroker::PerformDeferredBinding()
{
	if (bBoundToFramework) return;

	if (UWorld* World = GetGameInstance()->GetWorld())
	{
		BindToFramework();
		BindToUI(World);
		FS_INFO(FString("UFSGameInstanceBroker::PerformDeferredBinding → Framework + UI bound"));
	}
}

void UFSGameInstanceBroker::BindToFramework()
{
	if (bBoundToFramework) return;

	if (UWorld* World = GetGameInstance()->GetWorld())
	{
		GameFramework = World->GetSubsystem<UFSMenuGameFrameworkBroker>();
		if (!GameFramework)
		{
			FS_ERROR(FString("BindToFramework → UFSMenuGameFrameworkBroker not found"));
			return;
		}

		// ===== Use internal relays to forward EOS requests =====
		OnLoginRequested.AddDynamic(this, &UFSGameInstanceBroker::RelayLoginRequest);
		OnDevAuthRequested.AddDynamic(this, &UFSGameInstanceBroker::RelayDevAuthRequest);

		// ===== Subscribe to EOS completion =====
		GameFramework->LoginComplete.AddDynamic(this, &UFSGameInstanceBroker::HandleLoginFinished);
		GameFramework->DevAuthComplete.AddDynamic(this, &UFSGameInstanceBroker::HandleDevAuthFinished);

		bBoundToFramework = true;
	}
}

void UFSGameInstanceBroker::BindToUI(UWorld* World)
{
	if (bBoundToUI)
		return;

	MenuUI = World->GetSubsystem<UFSMenuUIBroker>();
	if (!MenuUI)
	{
		FS_WARN(FString("BindToUI → No UUFSMenuUIBroker found"));
		return;
	}

	MenuUI->OnLogin.AddDynamic(this, &UFSGameInstanceBroker::LoginEOS);
	MenuUI->OnDevAuth.AddDynamic(this, &UFSGameInstanceBroker::LoginEOS_Dev);
	MenuUI->OnGetPlayerName.AddDynamic(this, &UFSGameInstanceBroker::GetPlayerName);
	MenuUI->OnGetLoginStatus.AddDynamic(this, &UFSGameInstanceBroker::GetLoginStatus);

	bBoundToUI = true;
}

void UFSGameInstanceBroker::Deinitialize()
{
	Super::Deinitialize();
	GameFramework = nullptr;
	MenuUI = nullptr;
	bBoundToFramework = false;
	bBoundToUI = false;
}

// ======== Framework → Core Results ========

void UFSGameInstanceBroker::HandleLoginFinished(bool bSuccess, const FString& Error)
{
	OnLoginComplete.Broadcast(bSuccess, Error);
	if (MenuUI)
	{MenuUI->LoginResult(bSuccess, Error);}
}

void UFSGameInstanceBroker::HandleDevAuthFinished(bool bSuccess, const FString& Error)
{
	OnDevAuthComplete.Broadcast(bSuccess, Error);
	if (MenuUI)
	{MenuUI->DevAuthResult(bSuccess, Error);}
}

// ======== Internal Relay Handlers ========

void UFSGameInstanceBroker::RelayLoginRequest(const FString& ID, const FString& Token, const FString& Type)
{
	if (GameFramework)
		GameFramework->RequestEOSLogin.Broadcast(ID, Token, Type);
	else
		FS_ERROR(FString("RelayLoginRequest → GameFramework missing"));
}

void UFSGameInstanceBroker::RelayDevAuthRequest()
{
	if (GameFramework)
		GameFramework->RequestEOSDevAuth.Broadcast();
	else
		FS_ERROR(FString("RelayDevAuthRequest → GameFramework missing"));
}

// ======== UI → Core Routed Calls ========

void UFSGameInstanceBroker::LoginEOS(const FString& ID, const FString& Token, const FString& Type)
{
	OnLoginRequested.Broadcast(ID, Token, Type);
}

void UFSGameInstanceBroker::LoginEOS_Dev()
{
	OnDevAuthRequested.Broadcast();
}

void UFSGameInstanceBroker::GetPlayerName(FString& OutName)
{
	if (!GameFramework)
	{
		FS_ERROR(FString("GetPlayerName → GameFramework missing"));
		OutName = TEXT("Unknown");
		return;
	}
	OutName = GameFramework->GetPlayerName();
}

void UFSGameInstanceBroker::GetLoginStatus(bool& bIsLoggedIn)
{
	if (!GameFramework)
	{
		FS_ERROR(FString("GetLoginStatus → GameFramework missing"));
		bIsLoggedIn = false;
		return;
	}
	bIsLoggedIn = GameFramework->GetLoginStatus();
}
