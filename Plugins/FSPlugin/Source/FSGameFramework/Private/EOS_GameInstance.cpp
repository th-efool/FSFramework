// Fill out your copyright notice in the Description page of Project Settings.


#include "EOS_GameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include  "Interfaces/OnlineIdentityInterface.h"
#include "Utility/FSErrorHandler.h"


void UEOS_GameInstance::LoginWithEOS(const FString& ID, const FString& Token, const FString& LoginType)
{
	IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(GetWorld());
	if (!SubsystemRef)
	{
		FS_ERROR(FString("LoginWithEOS() → SubsystemRef invalid"));
		return;
	}

	IOnlineIdentityPtr IdentityRef = SubsystemRef->GetIdentityInterface();
	if (!IdentityRef.IsValid())
	{
		FS_ERROR(FString("LoginWithEOS() → IOnlineIdentityPtr invalid"));
		return;
	}

	FS_INFO(*FString::Printf(TEXT("EOS Login | Type: %s | ID: %s | Token: %s"), *LoginType, *ID, *Token));

	FOnlineAccountCredentials Creds;
	Creds.Id    = ID;
	Creds.Token = Token;
	Creds.Type  = LoginType;

	IdentityRef->OnLoginCompleteDelegates->AddUObject(this, &UEOS_GameInstance::LoginWithEOS_OnReturn);
	IdentityRef->Login(0, Creds);

	FS_INFO(FString("Login request dispatched to subsystem."));
}

void UEOS_GameInstance::LoginWithEOS_DevAuth()
{
	IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(GetWorld());
	if (!SubsystemRef)
	{
		FS_ERROR(FString("LoginWithEOS_DevAuth() → SubsystemRef invalid"));
		return;
	}

	IOnlineIdentityPtr IdentityRef = SubsystemRef->GetIdentityInterface();
	if (!IdentityRef.IsValid())
	{
		FS_ERROR(FString("LoginWithEOS_DevAuth() → IOnlineIdentityPtr invalid"));
		return;
	}

	const FString DevID        = TEXT("localhost:8081");
	const FString DevToken     = TEXT("pass1");
	const FString DevLoginType = TEXT("developer");

	FS_INFO(*FString::Printf(TEXT("EOS DevAuth | Host: %s | Token: %s"), *DevID, *DevToken));

	FOnlineAccountCredentials Creds;
	Creds.Id    = DevID;
	Creds.Token = DevToken;
	Creds.Type  = DevLoginType;

	IdentityRef->OnLoginCompleteDelegates->AddUObject(this, &UEOS_GameInstance::LoginWithEOS_OnReturn);
	IdentityRef->Login(0, Creds);

	FS_INFO(FString("DevAuth login request dispatched to subsystem."));
}

void UEOS_GameInstance::GetLoginStatus(bool& bIsLoggedIn)
{
	bIsLoggedIn = false;

	IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(GetWorld());
	if (!SubsystemRef)
	{
		FS_ERROR(FString("GetLoginStatus() → SubsystemRef invalid"));
		return;
	}

	IOnlineIdentityPtr IdentityRef = SubsystemRef->GetIdentityInterface();
	if (!IdentityRef.IsValid())
	{
		FS_ERROR(FString("GetLoginStatus() → IOnlineIdentityPtr invalid"));
		return;
	}

	const ELoginStatus::Type Status = IdentityRef->GetLoginStatus(0);
	bIsLoggedIn = (Status == ELoginStatus::LoggedIn);

	FS_INFO(*FString::Printf(TEXT("GetLoginStatus() → %s"), bIsLoggedIn ? TEXT("LoggedIn") : TEXT("NotLoggedIn")));
}

void UEOS_GameInstance::GetPlayerName(FString& OutPlayerName)
{
	OutPlayerName = TEXT("Unknown");

	IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(GetWorld());
	if (!SubsystemRef)
	{
		FS_ERROR(FString("GetPlayerName() → SubsystemRef invalid"));
		return;
	}

	IOnlineIdentityPtr IdentityRef = SubsystemRef->GetIdentityInterface();
	if (!IdentityRef.IsValid())
	{
		FS_ERROR(FString("GetPlayerName() → IOnlineIdentityPtr invalid"));
		return;
	}

	TSharedPtr<const FUniqueNetId> UserId = IdentityRef->GetUniquePlayerId(0);
	if (!UserId.IsValid())
	{
		FS_WARN(FString("GetPlayerName() → No valid UserId"));
		return;
	}

	OutPlayerName = IdentityRef->GetPlayerNickname(*UserId);
	FS_INFO(*FString::Printf(TEXT("GetPlayerName() → %s"), *OutPlayerName));
}

void UEOS_GameInstance::LoginWithEOS_OnReturn(int32 LocalUserNum, bool bWasSuccess, const FUniqueNetId& UserID, const FString& Error)
{
	if (bWasSuccess)
	{
		FS_INFO(FString("LoginWithEOS_OnReturn() → Login successful"));
	}
	else
	{
		FS_ERROR(*FString::Printf(TEXT("LoginWithEOS_OnReturn() → Login failed: %s"), *Error));
	}

	IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(GetWorld());
	if (!SubsystemRef) return;

	IOnlineIdentityPtr IdentityRef = SubsystemRef->GetIdentityInterface();
	if (!IdentityRef.IsValid()) return;

	IdentityRef->ClearOnLoginCompleteDelegates(LocalUserNum, this);
}

