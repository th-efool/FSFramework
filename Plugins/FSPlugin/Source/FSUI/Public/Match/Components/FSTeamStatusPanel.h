// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSTeamStatusPanelEntry.h"
#include "Base/FSHUDWidgetBase.h"
#include "Components/VerticalBox.h"
#include "Data/FSBrokerDataTypes.h"
#include "FSTeamStatusPanel.generated.h"


UCLASS()
class FSUI_API UFSTeamStatusPanel : public UFSComponentWidgetBase
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* PlayerListBox;

	UPROPERTY(EditDefaultsOnly, Category="PlayerPanel")
	TSubclassOf<UFSTeamStatusPanelEntry> PlayerEntryClass;

	UFUNCTION(BlueprintCallable)
	void AddPlayerEntry(const FString& Name, const FString& ID, UTexture2D* Avatar);

	
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;
	UFUNCTION(BlueprintCallable)
	void HandlePlayerJoined(const FPlayerJoinInfo& Info);
	UFUNCTION(BlueprintCallable)
	void HandlePlayerLeft(APlayerState* PlayerState);

	
	
};
