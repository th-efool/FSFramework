// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/FSMatchHUDWidget.h"

void UFSMatchHUDWidget::NativeConstruct()
{
	// Get the local Player Controller. This will be the Owner and WorldContext for creation.
	APlayerController* OwningPlayerController = GetOwningPlayer();

	// Safety check for the owner.
	if (!OwningPlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("UFSMatchHUDWidget::NativeConstruct - Failed to get OwningPlayerController."));
		return;
	}

	// 1. Construct PlayScreenHUD
	if (PlayScreenHUDClass)
	{
		// Direct creation. The template type (UFSPlayScreenHUDWidget) matches the variable type.
		PlayScreenHUDInstance = CreateWidget<UFSPlayScreenHUDWidget>(OwningPlayerController, PlayScreenHUDClass);

		if (PlayScreenHUDInstance)
		{
			// Assuming this is the default screen, it remains visible.
			UE_LOG(LogTemp, Log, TEXT("PlayScreenHUD constructed."));

			// ⭐ Remember to add to a visual container here: 
			// MyBoundCanvasPanel->AddChild(PlayScreenHUDInstance);
		}
		PlayScreenHUDInstance->AddToViewport();
	}

	// 2. Construct EndScreenHUD
	if (EndScreenHUDClass)
	{
		// Direct creation.
		EndScreenHUDInstance = CreateWidget<UFSEndScreenHUDWidget>(OwningPlayerController, EndScreenHUDClass);

		if (EndScreenHUDInstance)
		{
			// Set initial visibility to hidden.
			EndScreenHUDInstance->SetVisibility(ESlateVisibility::Collapsed);
			UE_LOG(LogTemp, Log, TEXT("EndScreenHUD constructed."));

			// ⭐ Add to a visual container here.
		}
	}

	// 3. Construct DeathScreenHUD
	if (DeathScreenHUDClass)
	{
		// Direct creation.
		DeathScreenHUDInstance = CreateWidget<UFSDeathScreenHUDWidget>(OwningPlayerController, DeathScreenHUDClass);

		if (DeathScreenHUDInstance)
		{
			// Set initial visibility to hidden.
			DeathScreenHUDInstance->SetVisibility(ESlateVisibility::Collapsed);
			UE_LOG(LogTemp, Log, TEXT("DeathScreenHUD constructed."));

			// ⭐ Add to a visual container here.
		}
	}
}
