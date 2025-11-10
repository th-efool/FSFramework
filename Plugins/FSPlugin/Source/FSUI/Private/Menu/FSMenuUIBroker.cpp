#include "Menu/FSMenuUIBroker.h"
#include "Utility/FSErrorHandler.h"

void UFSMenuUIBroker::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	FS_INFO(FString("UUFSMenuUIBroker::Initialize → Ready"));
}

void UFSMenuUIBroker::Deinitialize()
{
	Super::Deinitialize();
}

void UFSMenuUIBroker::Login(const FString& ID, const FString& Token, const FString& Type)
{
	OnLogin.Broadcast(ID, Token, Type);
	FS_INFO(*FString::Printf(TEXT("UI → Login | %s"), *ID));
}

void UFSMenuUIBroker::DevAuth()
{
	OnDevAuth.Broadcast();
	FS_INFO(FString("UI → DevAuth triggered"));
}

void UFSMenuUIBroker::GetPlayerName(FString& OutName)
{
	OnGetPlayerName.Broadcast(OutName);
	FS_INFO(*FString::Printf(TEXT("UI → GetPlayerName | %s"), *OutName));
}

void UFSMenuUIBroker::GetLoginStatus(bool& bIsLoggedIn)
{
	OnGetLoginStatus.Broadcast(bIsLoggedIn);
	FS_INFO(*FString::Printf(TEXT("UI → GetLoginStatus | %s"), bIsLoggedIn ? TEXT("true") : TEXT("false")));
}

void UFSMenuUIBroker::LoginResult(bool bSuccess, const FString& Error)
{
	OnLoginComplete.Broadcast(bSuccess, Error);
	FS_INFO(*FString::Printf(TEXT("UI ← LoginResult | %s"), bSuccess ? TEXT("OK") : TEXT("FAIL")));
}

void UFSMenuUIBroker::DevAuthResult(bool bSuccess, const FString& Error)
{
	OnDevAuthComplete.Broadcast(bSuccess, Error);
	FS_INFO(*FString::Printf(TEXT("UI ← DevAuthResult | %s"), bSuccess ? TEXT("OK") : TEXT("FAIL")));
}