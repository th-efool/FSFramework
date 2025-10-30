// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FSComponentWidgetBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "FSTextWithBackground.generated.h"

/**
 * 
 */
UCLASS()
class FSUI_API UFSTextWithBackground : public UFSComponentWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock;
	public:
	UPROPERTY(meta=(BindWidget))
	UImage* BackgroundImage;



public:
	UFUNCTION(BlueprintCallable)
	void SetText(FText InText);
	UFUNCTION(BlueprintCallable)
	void SetBackgroundImage(UTexture2D* InTexture);
	UFUNCTION(BlueprintCallable)
	void ShowForDuration(FText InText, float InDuration, float InFadeTime);
private:
public:
	float showElapsed = 0.f;
	float showDuration = 0.f;
	float fadeDuration = 0.f;

	FTimerHandle showTimerHandle;

	void TickShowAnimation(float deltaSeconds);
	void ApplyOpacity(const float normalizedAlpha) const;
};
