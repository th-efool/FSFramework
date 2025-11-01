// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FSHUDWidgetBase.h"
#include "Components/ProgressBar.h"
#include "Match/Components/FSArticle.h"
#include "Match/Components/FSInventory.h"
#include "Match/Components/FSTeamStatusPanel.h"
#include "Match/Components/FSTextWithBackground.h"
#include "FSPlayScreenHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class FSUI_API UFSPlayScreenHUDWidget : public UFSHUDWidgetBase
{
	GENERATED_BODY()

	public:
	UPROPERTY(meta=(BindWidget))
	UFSTeamStatusPanel* TeamStatusPanel;

	UPROPERTY(meta=(BindWidget))
	UFSArticle* DiaryEntry;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* Subtitles; 

	UPROPERTY(meta=(BindWidget))
	UFSInventory* Inventory;
	
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* Announcement;


	
	UPROPERTY(EditDefaultsOnly, Category="UI CLASSES")
	TSubclassOf<UFSTextWithBackground> SubtitleClass;

	UPROPERTY(EditDefaultsOnly, Category="UI CLASSES")
	TSubclassOf<UFSTextWithBackground> AnnouncementClass;
	
	UPROPERTY(meta=(BindWidget))
	UImage* CrossHair;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* Sanity;
	UPROPERTY(meta=(BindWidget))
	UProgressBar* Health;
	
	
	UFUNCTION(BlueprintCallable)
	void UpdateSanity(float percentage);
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float percentage);

	UFUNCTION(BlueprintCallable)
	void ShowAnnouncement(const FText& NewText, float time);
	UFUNCTION(BlueprintCallable)
	void ShowSubtitle(const FText& NewText, float time);
	UFUNCTION(BlueprintCallable)
	void ShowDiaryEntry(const FText& Date,const FText& Body );
	UFUNCTION(BlueprintCallable)
	void HideDiaryEntry();

	
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	
};
