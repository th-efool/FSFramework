// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/PlayScreen/FSPlayScreenHUDWidget.h"

#include "Match/Components/FSTextWithBackground.h"
#include "Components/VerticalBox.h"
#include "Components/ProgressBar.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Match/FSMatchUIBroker.h"
#include "Match/Components/FSArticle.h"
#include "Utility/FSErrorHandler.h"

// -----------------------------
// SANITY / HEALTH
// -----------------------------

void UFSPlayScreenHUDWidget::UpdateSanity(float percentage)
{
	if (!Sanity) return;
	Sanity->SetPercent(FMath::Clamp(percentage, 0.f, 1.f));
}

void UFSPlayScreenHUDWidget::UpdateHealth(float percentage)
{
	if (!Health) return;
	Health->SetPercent(FMath::Clamp(percentage, 0.f, 1.f));
}

// -----------------------------
// ANNOUNCEMENTS
// -----------------------------
void UFSPlayScreenHUDWidget::ShowAnnouncement(const FText& NewText, float time)
{
	if (!Announcement || !GetWorld()) return;

	UFSTextWithBackground* message = CreateWidget<UFSTextWithBackground>(GetWorld(), AnnouncementClass);
	if (!message) return;

	const float fade = 0.35f;
	message->ShowForDuration(NewText, time, fade);
	Announcement->AddChildToVerticalBox(message);

	FTimerHandle cleanupHandle;
	const float cleanupTime = time + fade * 2.f;

	GetWorld()->GetTimerManager().SetTimer(
		cleanupHandle,
		[this, message,NewText]()
		{
			if (Announcement && message)
			{
				Announcement->RemoveChild(message);
			}
		},
		cleanupTime,
		false
	);
}


// -----------------------------
// SUBTITLES
// -----------------------------
void UFSPlayScreenHUDWidget::ShowSubtitle(const FText& NewText, float time)
{
	if (!Subtitles || !GetWorld()) return;

	UFSTextWithBackground* subtitle = CreateWidget<UFSTextWithBackground>(GetWorld(), SubtitleClass);
	if (!subtitle) return;


	const float fade = 0.25f;
	subtitle->ShowForDuration(NewText, time, fade);
	Subtitles->AddChildToVerticalBox(subtitle);

	FTimerHandle cleanupHandle;
	const float cleanupTime = time + fade * 2.f;

	GetWorld()->GetTimerManager().SetTimer(
		cleanupHandle,
		[this, subtitle,NewText]()
		{
			if (Subtitles && subtitle)
			{
				Subtitles->RemoveChild(subtitle);
			}
		},
		cleanupTime,
		false
	);
}

// -----------------------------
// DIARY ENTRY (persistent)
// -----------------------------

void UFSPlayScreenHUDWidget::ShowDiaryEntry(const FText& Date, const FText& Body)
{
	if (!DiaryEntry) return;
	// diary shows immediately; you can add fade if desired
	DiaryEntry->ShowForDuration(Date,Body, 9999.f, 0.1f);
}

void UFSPlayScreenHUDWidget::HideDiaryEntry()
{
	if (!DiaryEntry) return;

	// fade out fast (diary isn't transient like subtitle)
	DiaryEntry->ClearShow();
}

void UFSPlayScreenHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UWorld* world = GetWorld();
	if (!world) return;

	UFSMatchUIBroker* broker = world->GetSubsystem<UFSMatchUIBroker>();
	if (!broker) return;

	// Gameplay -> UI bindings
	broker->OnUISanityChanged     .AddDynamic(this, &UFSPlayScreenHUDWidget::UpdateSanity);
	broker->OnUIHealthChanged     .AddDynamic(this, &UFSPlayScreenHUDWidget::UpdateHealth);

	broker->OnUIAnnouncement      .AddDynamic(this, &UFSPlayScreenHUDWidget::ShowAnnouncement);
	broker->OnUISubtitle          .AddDynamic(this, &UFSPlayScreenHUDWidget::ShowSubtitle);

	broker->OnUIDiaryShow         .AddDynamic(this, &UFSPlayScreenHUDWidget::ShowDiaryEntry);
	broker->OnUIDiaryHide         .AddDynamic(this, &UFSPlayScreenHUDWidget::HideDiaryEntry);
}

void UFSPlayScreenHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();
	UWorld* world = GetWorld();
	if (!world) return;

	UFSMatchUIBroker* broker = world->GetSubsystem<UFSMatchUIBroker>();
	if (!broker) return;

	broker->OnUISanityChanged     .RemoveDynamic(this, &UFSPlayScreenHUDWidget::UpdateSanity);
	broker->OnUIHealthChanged     .RemoveDynamic(this, &UFSPlayScreenHUDWidget::UpdateHealth);

	broker->OnUIAnnouncement      .RemoveDynamic(this, &UFSPlayScreenHUDWidget::ShowAnnouncement);
	broker->OnUISubtitle          .RemoveDynamic(this, &UFSPlayScreenHUDWidget::ShowSubtitle);

	broker->OnUIDiaryShow         .RemoveDynamic(this, &UFSPlayScreenHUDWidget::ShowDiaryEntry);
	broker->OnUIDiaryHide         .RemoveDynamic(this, &UFSPlayScreenHUDWidget::HideDiaryEntry);
}
