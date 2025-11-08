// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/FSMenuGameFrameworkBroker.h"
#include "EOS_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/FSErrorHandler.h"

void UFSMenuGameFrameworkBroker::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstanceRef = Cast<UEOS_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstanceRef)
	{
		FS_ERROR(FString("Broker Init → No valid UEOS_GameInstance found"));
		return;
	}

	// ========= Bind command requests =========
	RequestEOSLogin.AddDynamic(GameInstanceRef, &UEOS_GameInstance::LoginWithEOS);
	RequestEOSDevAuth.AddDynamic(GameInstanceRef, &UEOS_GameInstance::LoginWithEOS_DevAuth);

	// ========= Bind async login responses =========
	GameInstanceRef->LoginComplete.AddDynamic(this, &UFSMenuGameFrameworkBroker::HandleLoginComplete);
	GameInstanceRef->DevAuthComplete.AddDynamic(this, &UFSMenuGameFrameworkBroker::HandleDevAuthComplete);

	FS_INFO(FString("Broker successfully bound to EOS_GameInstance (one-way mode)"));
}

void UFSMenuGameFrameworkBroker::HandleLoginComplete(bool bSuccess, const FString& ErrorMessage)
{
	if (bSuccess)
	{
		FS_INFO(FString("Broker → LoginComplete: Success"));
	}
	else
	{
		FS_ERROR(*FString::Printf(TEXT("Broker → LoginComplete: Failed | %s"), *ErrorMessage));
	}

	LoginComplete.Broadcast(bSuccess, ErrorMessage);
}

void UFSMenuGameFrameworkBroker::HandleDevAuthComplete(bool bSuccess, const FString& ErrorMessage)
{
	if (bSuccess)
	{
		FS_INFO(FString("Broker → DevAuthComplete: Success"));
	}
	else
	{
		FS_ERROR(*FString::Printf(TEXT("Broker → DevAuthComplete: Failed | %s"), *ErrorMessage));
	}

	DevAuthComplete.Broadcast(bSuccess, ErrorMessage);
}

bool UFSMenuGameFrameworkBroker::GetLoginStatus()
{
	if (!GameInstanceRef)
	{
		FS_ERROR(FString("GetLoginStatus() → GameInstanceRef invalid"));
		return false;
	}

	bool bLoggedIn = false;
	GameInstanceRef->GetLoginStatus(bLoggedIn);

	FS_INFO(*FString::Printf(TEXT("GetLoginStatus() → %s"), bLoggedIn ? TEXT("LoggedIn") : TEXT("NotLoggedIn")));
	return bLoggedIn;
}

FString UFSMenuGameFrameworkBroker::GetPlayerName()
{
	if (!GameInstanceRef)
	{
		FS_ERROR(FString("GetPlayerName() → GameInstanceRef invalid"));
		return FString("Unknown");
	}

	FString PlayerName;
	GameInstanceRef->GetPlayerName(PlayerName);

	FS_INFO(*FString::Printf(TEXT("GetPlayerName() → %s"), *PlayerName));
	return PlayerName;
}
