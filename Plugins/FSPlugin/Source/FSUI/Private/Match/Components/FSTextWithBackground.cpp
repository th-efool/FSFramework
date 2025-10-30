// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/Components/FSTextWithBackground.h"

void UFSTextWithBackground::SetText(FText InText)
{
	TextBlock->SetText(InText);
}

void UFSTextWithBackground::SetBackgroundImage(UTexture2D* InTexture)
{
	BackgroundImage->SetBrushFromTexture(InTexture);
}

// .cpp

void UFSTextWithBackground::ShowForDuration(FText InText, float InDuration, float InFadeTime)
{
	SetText(InText);

	showElapsed     = 0.f;
	showDuration    = InDuration;
	fadeDuration    = InFadeTime;

	// ensure clean state
	ApplyOpacity(0.f);

	if (!GetWorld()) return;

	// tick every frame (0 interval = tick)
	GetWorld()->GetTimerManager().SetTimer(
		showTimerHandle,
		FTimerDelegate::CreateUObject(this, &UFSTextWithBackground::TickShowAnimation, GetWorld()->GetDeltaSeconds()),
		0.f,
		true
	);
}

void UFSTextWithBackground::TickShowAnimation(float deltaSeconds)
{
	showElapsed += deltaSeconds;

	const float totalLifetime = fadeDuration * 2.f + showDuration;

	// finished
	if (showElapsed >= totalLifetime)
	{
		ApplyOpacity(0.f);
		GetWorld()->GetTimerManager().ClearTimer(showTimerHandle);
		return;
	}

	// fade-in phase
	if (showElapsed < fadeDuration)
	{
		const float alpha = showElapsed / fadeDuration;
		ApplyOpacity(alpha);
		return;
	}

	// hold fully visible
	if (showElapsed < fadeDuration + showDuration)
	{
		ApplyOpacity(1.f);
		return;
	}

	// fade-out phase
	const float fadeOutElapsed = showElapsed - (fadeDuration + showDuration);
	const float alpha = 1.f - (fadeOutElapsed / fadeDuration);
	ApplyOpacity(alpha);
}

void UFSTextWithBackground::ApplyOpacity(const float normalizedAlpha) const
{
	if (TextBlock)
	{
		const FLinearColor color = FLinearColor(1,1,1, normalizedAlpha);
		TextBlock->SetColorAndOpacity(color);
	}

	if (BackgroundImage)
	{
		FLinearColor imageColor = BackgroundImage->GetColorAndOpacity();
		imageColor.A = normalizedAlpha;
		BackgroundImage->SetColorAndOpacity(imageColor);
	}
}
