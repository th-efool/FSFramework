// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/EventEnum.h"
#include "Subsystems/WorldSubsystem.h"
#include "FSEventManager.generated.h"

/**
 * 
 */
UCLASS()
class FSGAMEPLAY_API UFSEventManager : public UWorldSubsystem
{
	GENERATED_BODY()

	
	// Example: Trigger an event from your EEventType enum
	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerEvent(EFSEventEnum EventType, AActor* Instigator, const FSCustomEventParams& CustomEventParams);

	// Optional: Register/Unregister listeners if you want a broadcast system
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEventTriggered, EFSEventEnum, EventType, AActor*, Instigator);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnEventTriggered OnEventTriggered;

	UFUNCTION(BlueprintCallable, Category = "Events|Audio")
	void PlaySound(AActor* Instigator, USoundBase* Sound, FVector Location = FVector::ZeroVector,
				   float VolumeMultiplier = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Events|Lighting")
	void TriggerLightFlicker(AActor* Instigator, const TArray<TScriptInterface<IFSFlicker>>& FlickerActors,
							 float Duration = 1.f, float IntensityScale = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Events|Gameplay")
	void TeleportActor(AActor* Instigator, const FVector& TargetLocation);
};
