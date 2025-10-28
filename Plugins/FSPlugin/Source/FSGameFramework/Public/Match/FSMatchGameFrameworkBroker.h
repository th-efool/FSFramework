// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "FSCore/Public/Data/FSBrokerDataTypes.h"
#include "FSMatchGameFrameworkBroker.generated.h"

/**
 * 
 */
UCLASS()
class FSGAMEFRAMEWORK_API UFSMatchGameFrameworkBroker : public UWorldSubsystem
{
	GENERATED_BODY()
	public:
	UPROPERTY(BlueprintAssignable, Category = "FS|Match")
	FPlayerJoinedSignature OnPlayerJoined;
	
	UFUNCTION(BlueprintCallable, Category = "FS|Match")
	void NotifyPlayerJoined(APlayerController* PC); //Instead Of Calling Broadcast through child class, call broadcast through this

	UPROPERTY(BlueprintAssignable, Category = "FS|Match")
	FPlayerLeftSignature  OnPlayerLeft;
	UFUNCTION(BlueprintCallable, Category = "FS|Match")
	void NotifyPlayerLeft(APlayerState* PS); //Instead Of Calling Broadcast through child class, call broadcast through this


};
