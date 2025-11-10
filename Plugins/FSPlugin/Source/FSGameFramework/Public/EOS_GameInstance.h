#pragma once

#include "CoreMinimal.h"
#include "FSGameInstanceBase.h"
#include "Data/FSBrokerDataTypes.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "EOS_GameInstance.generated.h"

// ===========================================================
// Delegates — only for async ops
// ===========================================================

UCLASS()
class FSGAMEFRAMEWORK_API UEOS_GameInstance : public UFSGameInstanceBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "EOS | Delegates")
	FLoginComplete LoginComplete;

	UPROPERTY(BlueprintAssignable, Category = "EOS | Delegates")
	FDevAuthComplete DevAuthComplete;

	// ======= Core EOS Actions =======
	UFUNCTION(BlueprintCallable, Category = "EOS | Function")
	void LoginWithEOS(const FString& ID, const FString& Token, const FString& LoginType);

	UFUNCTION(BlueprintCallable, Category = "EOS | Function")
	void LoginWithEOS_DevAuth();

	void LoginWithEOS_OnReturn(int32 LocalUserNum, bool bWasSuccess, const FUniqueNetId& UserID, const FString& Error);

	// ======= Direct Getters (sync fill by ref) =======
	UFUNCTION(BlueprintCallable, Category = "EOS | Function")
	void GetLoginStatus(bool& bIsLoggedIn);

	UFUNCTION(BlueprintCallable, Category = "EOS | Function")
	void GetPlayerName(FString& OutPlayerName);
};
