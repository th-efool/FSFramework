// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/Components/FSArticle.h"
#include "TimerManager.h"
#include "Engine/World.h"

// ---------------------
// BASIC SETTERS
// ---------------------

void UFSArticle::SetTitle(const FText& NewTitle)
{
	if (!ArticleTitle) return;
	ArticleTitle->SetText(NewTitle);
}

void UFSArticle::SetBody(const FText& NewBody)
{
	if (!ArticleBody) return;
	ArticleBody->SetText(NewBody);
}

void UFSArticle::SetBackgroundImage(UTexture2D* NewTexture)
{
	if (!ArticleBackground) return;
	ArticleBackground->SetBrushFromTexture(NewTexture);
}

// ---------------------
// ANIMATED SHOW
// ---------------------

void UFSArticle::ShowForDuration(const FText& TitleText, const FText& BodyText, float VisibleTime, float FadeTime)
{
	SetTitle(TitleText);
	SetBody(BodyText);

	showElapsed = 0.f;
	showDuration = VisibleTime;
	fadeDuration = FadeTime;
	
	if (!GetWorld()) return;
	if (!FadeInAnimation){return;}
	float playbackSpeed = (fadeDuration>0)? 1.f/fadeDuration : 99999.9f;
	PlayAnimation(FadeInAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, playbackSpeed);

	GetWorld()->GetTimerManager().ClearTimer(showTimerHandle);

	// Fire every frame
	GetWorld()->GetTimerManager().SetTimer(
		showTimerHandle,
		[this,playbackSpeed]()
				{
					if (!FadeInAnimation){return;}
					PlayAnimation(FadeInAnimation, 0.f, 1, EUMGSequencePlayMode::Reverse, playbackSpeed);
				},
		showDuration-fadeDuration,
		true
	);
}
void UFSArticle::ClearShow()
{
	if (!GetWorld()) return;

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(showTimerHandle))
	{
		// 🔹 Manually trigger what the timer was going to call
		if (FadeInAnimation)
		{
			const float playbackSpeed = 100.f; // or whatever value you had
			PlayAnimation(FadeInAnimation, 0.f, 1, EUMGSequencePlayMode::Reverse, playbackSpeed);
		}

		// 🔹 Then clear timer
		TimerManager.ClearTimer(showTimerHandle);
	}

	showElapsed = 0.f;
	showDuration = 0.f;
	fadeDuration = 0.f;
}



