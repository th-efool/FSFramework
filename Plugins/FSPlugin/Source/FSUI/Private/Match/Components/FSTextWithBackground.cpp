// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/Components/FSTextWithBackground.h"

#include "Utility/FSErrorHandler.h"

void UFSTextWithBackground::SetText(FText InText)
{
	TextBlock->SetText(InText);
}

void UFSTextWithBackground::SetBackgroundImage(UTexture2D* InTexture)
{
	Background->SetBrushFromTexture(InTexture);
}

// .cpp

void UFSTextWithBackground::ShowForDuration(FText InText, float InDuration, float InFadeTime)
{
	SetText(InText);

	showElapsed     = 0.f;
	showDuration    = InDuration;
	fadeDuration    = InFadeTime;


	if (!GetWorld()) return;

	if (!FadeInAnimation){return;}
	float playbackSpeed = (fadeDuration>0)? 1.f/fadeDuration : 99999.9f;
	PlayAnimation(FadeInAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, playbackSpeed);
	
	GetWorld()->GetTimerManager().SetTimer(
		showTimerHandle,
				[this,playbackSpeed]()
				{
					if (!FadeInAnimation){return;}
					PlayAnimation(FadeInAnimation, 0.f, 1, EUMGSequencePlayMode::Reverse, playbackSpeed);
				},
		showDuration-fadeDuration,
		false
	);
}



