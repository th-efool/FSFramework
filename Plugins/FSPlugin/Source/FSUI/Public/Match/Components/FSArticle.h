// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FSComponentWidgetBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "FSArticle.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FSUI_API UFSArticle : public UFSComponentWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ArticleTitle;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ArticleBody;
	UPROPERTY(meta=(BindWidget))
	UImage* ArticleBackground;
	// API
	void SetTitle(const FText& NewTitle);
	void SetBody(const FText& NewBody);
	void SetBackgroundImage(UTexture2D* NewTexture);

	void ShowForDuration(const FText& NewTitle, const FText& BodyText, float VisibleTime, float FadeTime);
	void ClearShow();
private:
	void TickShow(float deltaTime);
	void ApplyOpacity(float InAlpha);

	FTimerHandle ShowTimerHandle;

	float Elapsed = 0.f;
	float HoldDuration = 0.f;
	float FadeDuration = 0.f;

};
