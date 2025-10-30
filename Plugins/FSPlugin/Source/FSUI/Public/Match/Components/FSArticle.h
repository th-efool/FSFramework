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
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FadeInAnimation;

};
