#pragma once

#include "CoreMinimal.h"
#include "Data/FSBrokerDataTypes.h"
#include "Subsystems/WorldSubsystem.h"
#include "FSMenuGameFrameworkBroker.generated.h"



UCLASS()
class FSGAMEFRAMEWORK_API UFSMenuGameFrameworkBroker : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// ===== Requests =====
	UPROPERTY(BlueprintAssignable, Category = "EOS | Requests")
	FRequestEOSLogin RequestEOSLogin;

	UPROPERTY(BlueprintAssignable, Category = "EOS | Requests")
	FRequestEOSDevAuth RequestEOSDevAuth;

	// ===== Async Responses =====
	UPROPERTY(BlueprintAssignable, Category = "EOS | Responses")
	FLoginComplete LoginComplete;

	UPROPERTY(BlueprintAssignable, Category = "EOS | Responses")
	FDevAuthComplete DevAuthComplete;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	UPROPERTY() TObjectPtr<class UEOS_GameInstance> GameInstanceRef;

public:
	// ===== Direct getters (no delegate broadcasting) =====
	UFUNCTION(BlueprintCallable, Category = "EOS | Direct")
	bool GetLoginStatus();

	UFUNCTION(BlueprintCallable, Category = "EOS | Direct")
	FString GetPlayerName();

	UFUNCTION(BlueprintCallable, Category = "EOS | Direct")
	inline void EOSDevAuth()
	{
		RequestEOSDevAuth.Broadcast();
	}
	

private:
	UFUNCTION()
	void HandleLoginComplete(bool bSuccess, const FString& ErrorMessage);

	UFUNCTION()
	void HandleDevAuthComplete(bool bSuccess, const FString& ErrorMessage);
	
};
