// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FSGameModeBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class FSGAMEFRAMEWORK_API AFSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFSGameModeBase();

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
};
