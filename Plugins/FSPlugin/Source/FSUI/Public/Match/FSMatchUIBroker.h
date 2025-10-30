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

	UPROPERTY(BlueprintAssignable, Category="FS|UI") FSanityChangedSignature     OnUISanityChanged;
	UPROPERTY(BlueprintAssignable, Category="FS|UI") FHealthChangedSignature     OnUIHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="FS|UI") FAnnouncementSignature       OnUIAnnouncement;
	UPROPERTY(BlueprintAssignable, Category="FS|UI") FSubtitleSignature          OnUISubtitle;

	UPROPERTY(BlueprintAssignable, Category="FS|UI") FDiaryShowSignature         OnUIDiaryShow;
	UPROPERTY(BlueprintAssignable, Category="FS|UI") FDiaryHideSignature         OnUIDiaryHide;

	public:
	// Global UI-facing events — broadcast-only, persistent for the lifetime of the GameInstance
	UPROPERTY(BlueprintAssignable, Category = "FS|UI")
	FPlayerJoinedSignature OnUIPlayerJoined;
	UPROPERTY(BlueprintAssignable, Category = "FS|UI")
	FPlayerLeftSignature   OnUIPlayerLeft;


	// -------- Blueprint Relay API --------
	UFUNCTION(BlueprintCallable, Category="FS|UI|Relay")
	void RelaySanity(float newPercentage);

	UFUNCTION(BlueprintCallable, Category="FS|UI|Relay")
	void RelayHealth(float newPercentage);

	UFUNCTION(BlueprintCallable, Category="FS|UI|Relay")
	void RelayAnnouncement(const FText& text, float lifetime);

	UFUNCTION(BlueprintCallable, Category="FS|UI|Relay")
	void RelaySubtitle(const FText& text, float lifetime);

	UFUNCTION(BlueprintCallable, Category="FS|UI|Relay")
	void RelayDiaryShow(const FText& date, const FText& body);

	UFUNCTION(BlueprintCallable, Category="FS|UI|Relay")
	void RelayDiaryHide();
};

