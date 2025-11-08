#include "Menu/UFSMenuUIBroker.h"
#include "Utility/FSErrorHandler.h"

void UUFSMenuUIBroker::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	FS_INFO(FString("UUFSMenuUIBroker::Initialize → Ready"));
}

void UUFSMenuUIBroker::Deinitialize()
{
	Super::Deinitialize();
}

void UUFSMenuUIBroker::Login(const FString& ID, const FString& Token, const FString& Type)
{
	OnLogin.Broadcast(ID, Token, Type);
	FS_INFO(*FString::Printf(TEXT("UI → Login | %s"), *ID));
}

void UUFSMenuUIBroker::DevAuth()
{
	OnDevAuth.Broadcast();
	FS_INFO(FString("UI → DevAuth triggered"));
}

void UUFSMenuUIBroker::GetPlayerName(FString& OutName)
{
	OnGetPlayerName.Broadcast(OutName);
	FS_INFO(*FString::Printf(TEXT("UI → GetPlayerName | %s"), *OutName));
}

void UUFSMenuUIBroker::GetLoginStatus(bool& bIsLoggedIn)
{
	OnGetLoginStatus.Broadcast(bIsLoggedIn);
	FS_INFO(*FString::Printf(TEXT("UI → GetLoginStatus | %s"), bIsLoggedIn ? TEXT("true") : TEXT("false")));
}

void UUFSMenuUIBroker::LoginResult(bool bSuccess, const FString& Error)
{
	OnLoginComplete.Broadcast(bSuccess, Error);
	FS_INFO(*FString::Printf(TEXT("UI ← LoginResult | %s"), bSuccess ? TEXT("OK") : TEXT("FAIL")));
}

void UUFSMenuUIBroker::DevAuthResult(bool bSuccess, const FString& Error)
{
	OnDevAuthComplete.Broadcast(bSuccess, Error);
	FS_INFO(*FString::Printf(TEXT("UI ← DevAuthResult | %s"), bSuccess ? TEXT("OK") : TEXT("FAIL")));
}
