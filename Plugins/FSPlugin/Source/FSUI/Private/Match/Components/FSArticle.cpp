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

	Elapsed = 0.f;
	HoldDuration = VisibleTime;
	FadeDuration = FadeTime;

	ApplyOpacity(0.f);

	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().ClearTimer(ShowTimerHandle);

	// Fire every frame
	GetWorld()->GetTimerManager().SetTimer(
		ShowTimerHandle,
		[this]() { TickShow(GetWorld()->GetDeltaSeconds()); },
		0.f,
		true
	);
}

void UFSArticle::ClearShow()
{
	// if no timer, nothing to clear
	if (!GetWorld() || !GetWorld()->GetTimerManager().IsTimerActive(ShowTimerHandle))
		return;

	// stop ticking the show animation
	GetWorld()->GetTimerManager().ClearTimer(ShowTimerHandle);

	// reset state
	Elapsed = 0.f;
	HoldDuration = 0.f;
	FadeDuration = 0.f;

	// fully hide immediately
	ApplyOpacity(0.f);

}


void UFSArticle::TickShow(float dt)
{
	Elapsed += dt;

	const float TotalLifetime = FadeDuration * 2.f + HoldDuration;

	// finished
	if (Elapsed >= TotalLifetime)
	{
		ApplyOpacity(0.f);
		GetWorld()->GetTimerManager().ClearTimer(ShowTimerHandle);
		return;
	}

	// fade in
	if (Elapsed < FadeDuration)
	{
		const float alpha = Elapsed / FadeDuration;
		ApplyOpacity(alpha);
		return;
	}

	// hold fully visible
	if (Elapsed < FadeDuration + HoldDuration)
	{
		ApplyOpacity(1.f);
		return;
	}

	// fade out
	const float timeOut = Elapsed - (FadeDuration + HoldDuration);
	const float alpha = 1.f - (timeOut / FadeDuration);
	ApplyOpacity(alpha);
}

void UFSArticle::ApplyOpacity(float alpha)
{
	alpha = FMath::Clamp(alpha, 0.f, 1.f);

	if (ArticleTitle)
	{
		ArticleTitle->SetColorAndOpacity(FLinearColor(1.f,1.f,1.f, alpha));
	}

	if (ArticleBody)
	{
		ArticleBody->SetColorAndOpacity(FLinearColor(1.f,1.f,1.f, alpha));
	}

	if (ArticleBackground)
	{
		FLinearColor bg = ArticleBackground->GetColorAndOpacity();
		bg.A = alpha;
		ArticleBackground->SetColorAndOpacity(bg);
	}
}
