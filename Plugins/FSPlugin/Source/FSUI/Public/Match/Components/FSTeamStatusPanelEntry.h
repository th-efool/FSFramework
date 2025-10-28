// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FSComponentWidgetBase.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Base/FSHUDWidgetBase.h"
#include "FSTeamStatusPanelEntry.generated.h"

/**
 * 
 */
UCLASS()
class FSUI_API UFSTeamStatusPanelEntry : public UFSComponentWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerNameText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerIDText;

	UPROPERTY(meta=(BindWidget))
	UImage* PlayerAvatar;

	UPROPERTY(meta=(BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HorizontalBox;

	void SetBackgroundColor(const FLinearColor& Color) const;
	void InitializeEntry(const FString& InName, const FString& InID, UTexture2D* InAvatar) const;

	virtual void NativeConstruct() override;
};
