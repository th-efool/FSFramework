#pragma once

#include "CoreMinimal.h"
#include "Base/FSUIBrokerBase.h"
#include "Data/FSBrokerDataTypes.h"
#include "UFSMenuUIBroker.generated.h"

/**
 * Pure UI-side broker.
 * Emits EOS requests and exposes simple GetName/GetStatus queries.
 */
UCLASS()
class FSUI_API UUFSMenuUIBroker : public UFSUIBrokerBase
{
	GENERATED_BODY()

public:
	// ===== EOS Requests =====
	UPROPERTY(BlueprintAssignable, Category="UI | EOS")
	FRequestEOSLogin OnLogin;

	UPROPERTY(BlueprintAssignable, Category="UI | EOS")
	FRequestEOSDevAuth OnDevAuth;

	// ===== Query Requests =====
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetPlayerName, FString&, OutName);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetLoginStatus, bool&, bIsLoggedIn);

	UPROPERTY(BlueprintAssignable, Category="UI | EOS")
	FGetPlayerName OnGetPlayerName;

	UPROPERTY(BlueprintAssignable, Category="UI | EOS")
	FGetLoginStatus OnGetLoginStatus;

	// ===== Results (for UI display only) =====
	UPROPERTY(BlueprintAssignable, Category="UI | EOS")
	FLoginComplete OnLoginComplete;

	UPROPERTY(BlueprintAssignable, Category="UI | EOS")
	FDevAuthComplete OnDevAuthComplete;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// ===== Blueprint Access =====
	UFUNCTION(BlueprintCallable, Category="UI | EOS")
	void Login(const FString& ID, const FString& Token, const FString& Type);

	UFUNCTION(BlueprintCallable, Category="UI | EOS")
	void DevAuth();

	UFUNCTION(BlueprintCallable, Category="UI | EOS")
	void GetPlayerName(FString& OutName);

	UFUNCTION(BlueprintCallable, Category="UI | EOS")
	void GetLoginStatus(bool& bIsLoggedIn);

	// ===== Results Called by GameInstanceBroker =====
	UFUNCTION()
	void LoginResult(bool bSuccess, const FString& Error);

	UFUNCTION()
	void DevAuthResult(bool bSuccess, const FString& Error);
};
