// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FSUIBrokerBase.h"
#include "Data/FSBrokerDataTypes.h"
#include "FSMatchUIBroker.generated.h"

/**
 * 
 */
UCLASS()
class FSUI_API UFSMatchUIBroker : public UFSUIBrokerBase
{
	GENERATED_BODY()

	public:

	// Global UI-facing events — broadcast-only, persistent for the lifetime of the GameInstance
	UPROPERTY(BlueprintAssignable, Category = "FS|UI")
	FPlayerJoinedSignature OnUIPlayerJoined;
	UPROPERTY(BlueprintAssignable, Category = "FS|UI")
	FPlayerLeftSignature   OnUIPlayerLeft;
	
};

