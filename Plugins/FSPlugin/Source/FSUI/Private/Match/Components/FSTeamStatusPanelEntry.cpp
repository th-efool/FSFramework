// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/Components/FSTeamStatusPanelEntry.h"

#include "Utility/FSErrorHandler.h"


void UFSTeamStatusPanelEntry::SetBackgroundColor(const FLinearColor& Color) const
{
	BackgroundBorder->SetBrushColor(Color);
}

void UFSTeamStatusPanelEntry::InitializeEntry(const FString& InName, const FString& InID, UTexture2D* InAvatar) const
{
	if (PlayerNameText)
	{
		PlayerNameText->SetText(FText::FromString(InName));
	}
	if (PlayerIDText)
	{
		PlayerIDText->SetText(FText::FromString(InID));
	}
	if (PlayerAvatar && InAvatar)
	{
		PlayerAvatar->SetBrushFromTexture(InAvatar);
	}
}

void UFSTeamStatusPanelEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackgroundBorder && HorizontalBox)
	{
		if (UPanelWidget* OldParent = HorizontalBox->GetParent())
		{
			OldParent->RemoveChild(HorizontalBox);
		}

		BackgroundBorder->AddChild(HorizontalBox);
	}

	if (HorizontalBox)
	{
		if (PlayerNameText)
		{
			HorizontalBox->AddChild(PlayerNameText);
		}
		if (PlayerIDText)
		{
			HorizontalBox->AddChild(PlayerIDText);
		}
		if (PlayerAvatar)
		{
			HorizontalBox->AddChild(PlayerAvatar);
		}
	}
}
