#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/FSBrokerDataTypes.h"
#include "FSGameInstanceBroker.generated.h"

class UFSMenuUIBroker;
class UFSMenuGameFrameworkBroker;

/**
 * GameInstance-level broker bridging UI <-> GameFrameworkBroker.
 * Uses existing UFSMenuGameFrameworkBroker delegates and getters.
 * Does NOT modify or depend directly on UEOS_GameInstance.
 */
UCLASS()
class FSPLUGIN_API UFSGameInstanceBroker : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// ===== Forwarded Delegates =====
	UPROPERTY(BlueprintAssignable, Category="EOS | Requests")
	FRequestEOSLogin OnLoginRequested;

	UPROPERTY(BlueprintAssignable, Category="EOS | Requests")
	FRequestEOSDevAuth OnDevAuthRequested;

	UPROPERTY(BlueprintAssignable, Category="EOS | Responses")
	FLoginComplete OnLoginComplete;

	UPROPERTY(BlueprintAssignable, Category="EOS | Responses")
	FDevAuthComplete OnDevAuthComplete;

protected:
	UPROPERTY() TObjectPtr<UFSMenuGameFrameworkBroker> GameFramework = nullptr;
	UPROPERTY() TObjectPtr<UFSMenuUIBroker> MenuUI = nullptr;

	bool bBoundToFramework = false;
	bool bBoundToUI = false;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void PerformDeferredBinding();
	void BindToFramework();
	void BindToUI(UWorld* World);

	// ===== Handlers =====
	UFUNCTION(BlueprintCallable, Category = "EOS | Requests")
	void HandleLoginFinished(bool bSuccess, const FString& Error);

	UFUNCTION(BlueprintCallable, Category = "EOS | Requests")
	void HandleDevAuthFinished(bool bSuccess, const FString& Error);

	// ===== Routed Calls from UI Broker =====
	UFUNCTION(BlueprintCallable, Category = "EOS | Requests")
	void LoginEOS(const FString& ID, const FString& Token, const FString& Type);

	UFUNCTION(BlueprintCallable, Category = "EOS | Requests")
	void LoginEOS_Dev();

	UFUNCTION(BlueprintCallable, Category = "EOS | Requests")
	void GetPlayerName(FString& OutName);

	UFUNCTION(BlueprintCallable, Category = "EOS | Requests")
	void GetLoginStatus(bool& bIsLoggedIn);

private:
	// === Internal relays for EOS request forwarding ===
	UFUNCTION()
	void RelayLoginRequest(const FString& ID, const FString& Token, const FString& Type);

	UFUNCTION()
	void RelayDevAuthRequest();
};
