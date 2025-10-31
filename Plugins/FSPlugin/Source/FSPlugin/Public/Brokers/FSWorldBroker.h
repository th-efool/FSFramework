// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FSBrokerDataTypes.h"
#include "Match/FSMatchGameFrameworkBroker.h"
#include "Match/FSMatchUIBroker.h"
#include "Subsystems/WorldSubsystem.h"
#include "Systems/FSGameplayBroker.h"
#include "FSWorldBroker.generated.h"

/**
 * 
 */
UCLASS()
class FSPLUGIN_API UFSWorldBroker : public UWorldSubsystem
{
	GENERATED_BODY()

	// Global UI-facing events — broadcast-only, persistent for the lifetime of the GameInstance
	UPROPERTY(BlueprintAssignable, Category = "FS|Match")
	FPlayerJoinedSignature OnPlayerJoined;
	UPROPERTY(BlueprintAssignable, Category = "FS|Match")
	FPlayerLeftSignature   OnPlayerLeft;

	UPROPERTY()
	FInventoryItemAddedSignature OnInventoryItemAdded;
	UPROPERTY()
	FInventoryItemRemovedSignature OnInventoryItemRemoved;
	UPROPERTY()
	FGetInventory OnGetInventory;
	
	// --- UI HUD Event Delegates ---
	UPROPERTY(BlueprintAssignable, Category="FS|HUD")
	FSanityChangedSignature OnSanityChanged;

	UPROPERTY(BlueprintAssignable, Category="FS|HUD")
	FHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="FS|HUD")
	FAnnouncementSignature OnAnnouncement;

	UPROPERTY(BlueprintAssignable, Category="FS|HUD")
	FSubtitleSignature OnSubtitle;

	UPROPERTY(BlueprintAssignable, Category="FS|HUD")
	FDiaryShowSignature OnDiaryShow;

	UPROPERTY(BlueprintAssignable, Category="FS|HUD")
	FDiaryHideSignature OnDiaryHide;

	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	inline UFSMatchUIBroker* GetUIBroker(UWorld* World)
	{
		return World ? World->GetSubsystem<UFSMatchUIBroker>() : nullptr;
	}
	inline UFSMatchGameFrameworkBroker* GetGameFrameworkBroker(UWorld* World)
	{
		return World ? World->GetSubsystem<UFSMatchGameFrameworkBroker>() : nullptr;
	}
	inline UFSGameplayBroker* GetGameplayBroker(UWorld* World)
	{
		return World ? World->GetSubsystem<UFSGameplayBroker>() : nullptr;
	}

protected:
	UFUNCTION(BlueprintCallable)
	void HandlePlayerJoined(const FPlayerJoinInfo& Info);
	UFUNCTION(BlueprintCallable)
	void HandlePlayerLeft(APlayerState* PS);
	UFUNCTION()
	void HandleSanityChanged(float Percent);

	UFUNCTION()
	void HandleHealthChanged(float Percent);

	UFUNCTION()
	void HandleAnnouncement(const FText& Msg, float Time);

	UFUNCTION()
	void HandleSubtitle(const FText& Msg, float Time);

	UFUNCTION()
	void HandleDiaryShow(const FText& Date, const FText& Body);

	UFUNCTION()
	void HandleDiaryHide();

	UFUNCTION()
	void HandleGetInventory(FInventoryData& EmptyInventory);
	UFUNCTION()
	void HandleInventoryItemAdded(EInventoryItem Item, int Amount);
	UFUNCTION()
	void HandleInventoryItemRemoved(EInventoryItem Item, int Amount);
};
