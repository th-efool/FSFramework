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

	// Global UI-facing events — broadcast-only, persistent for the lifetime of the GameInstance
	UPROPERTY()
	FPlayerJoinedSignature OnPlayerJoined;
	UPROPERTY()
	FPlayerLeftSignature   OnPlayerLeft;

	UPROPERTY() FSanityChangedSignature OnSanityChanged;
	UPROPERTY() FHealthChangedSignature OnHealthChanged;


	// Example: Trigger an event from your EEventType enum
	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerEvent(EFSEventEnum EventType, AActor* Instigator, const FSCustomEventParams& CustomEventParams);

	// Optional: Register/Unregister listeners if you want a broadcast system
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEventTriggered, EFSEventEnum, EventType, AActor*, Instigator);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnEventTriggered OnEventTriggered;

	UFUNCTION(BlueprintCallable, Category = "Events|UI")
	void ShowMessage(AActor* Instigator, const FText& Message, float Duration = 3.f, FColor TextColor = FColor::White);

	UFUNCTION(BlueprintCallable, Category = "Events|UI")
	void ShowSubtitle(AActor* Instigator, const FText& Subtitle, AActor* Speaker = nullptr, float Duration = 2.f);

	UFUNCTION(BlueprintCallable, Category = "Events|UI")
	void ShowAnnouncement(AActor* Instigator, const FText& Title, const FText& Body, float DisplayTime = 5.f,
	                      USoundBase* AnnouncementSound = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Events|Audio")
	void PlaySound(AActor* Instigator, USoundBase* Sound, FVector Location = FVector::ZeroVector,
	               float VolumeMultiplier = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Events|Lighting")
	void TriggerLightFlicker(AActor* Instigator, const TArray<TScriptInterface<IFSFlicker>>& FlickerActors,
	                         float Duration = 1.f, float IntensityScale = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Events|Gameplay")
	void TeleportActor(AActor* Instigator, const FVector& TargetLocation);


	// -------- Blueprint Call/Relay API --------
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RelayInventoryItemAdded(EInventoryItem Item, int Amount);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RelayInventoryItemRemoved(EInventoryItem Item, int Amount);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RelayGetInventory(FInventoryData& Inventory);
};
