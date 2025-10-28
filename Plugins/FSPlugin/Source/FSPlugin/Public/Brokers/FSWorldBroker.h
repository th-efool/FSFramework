// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FSBrokerDataTypes.h"
#include "Subsystems/WorldSubsystem.h"
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

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION()
	void HandlePlayerJoined(const FPlayerJoinInfo& Info);
	UFUNCTION()
	void HandlePlayerLeft(APlayerState* PS);

};
