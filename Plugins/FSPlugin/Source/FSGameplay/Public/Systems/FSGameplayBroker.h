// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FSBrokerDataTypes.h"
#include "Enums/EventEnum.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FSGameplayBroker.generated.h"

UCLASS()
class FSGAMEPLAY_API UFSGameplayBroker : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FInventoryItemAddedSignature OnInventoryItemAdded;
	UPROPERTY()
	FInventoryItemRemovedSignature OnInventoryItemRemoved;
	UPROPERTY()
	FGetInventory OnGetInventory;

	UPROPERTY()
	FOnHasItem OnHasItem;

	// Global UI-facing events — broadcast-only, persistent for the lifetime of the GameInstance
	UPROPERTY()
	FPlayerJoinedSignature OnPlayerJoined;
	UPROPERTY()
	FPlayerLeftSignature   OnPlayerLeft;

	UPROPERTY() FSanityChangedSignature OnSanityChanged;
	UPROPERTY() FHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="FS|HUD")
	FOnInventoryItemConsumed OnConsumeItemButtonPressed;

	UPROPERTY(BlueprintAssignable, Category="FS|HUD")
	FOnInventoryItemDropped OnDropItemButtonPressed;
	

	// -------- Blueprint Call/Relay API --------
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RelayInventoryItemAdded(EInventoryItem Item, int Amount);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RelayInventoryItemRemoved(EInventoryItem Item, int Amount);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RelayGetInventory(FInventoryData& Inventory);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool HasItem(EInventoryItem Item);
};
