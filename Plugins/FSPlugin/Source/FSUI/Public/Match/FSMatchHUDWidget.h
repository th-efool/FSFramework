// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FSHUDWidgetBase.h"
#include "DeathScreen/FSDeathScreenHUDWidget.h"
#include "EndScreen/FSEndScreenHUDWidget.h"
#include "PlayScreen/FSPlayScreenHUDWidget.h"
#include "FSMatchHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class FSUI_API UFSMatchHUDWidget : public UFSHUDWidgetBase
{
	GENERATED_BODY()

public:
	// Pointers to hold the instances after creation
	UPROPERTY(VisibleInstanceOnly, Category="MatchMenus")
	UFSPlayScreenHUDWidget* PlayScreenHUDInstance;

	UPROPERTY(VisibleInstanceOnly, Category="MatchMenus")
	UFSEndScreenHUDWidget* EndScreenHUDInstance;

	UPROPERTY(VisibleInstanceOnly, Category="MatchMenus")
	UFSDeathScreenHUDWidget* DeathScreenHUDInstance;

protected:
	// Override function where construction happens
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, Category="MatchMenus")
	TSubclassOf<UFSPlayScreenHUDWidget> PlayScreenHUDClass;
	UPROPERTY(EditDefaultsOnly, Category="MatchMenus")
	TSubclassOf<UFSEndScreenHUDWidget> EndScreenHUDClass;
	UPROPERTY(EditDefaultsOnly, Category="MatchMenus")
	TSubclassOf<UFSDeathScreenHUDWidget> DeathScreenHUDClass;
};
