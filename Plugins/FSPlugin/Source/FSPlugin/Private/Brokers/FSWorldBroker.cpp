// Fill out your copyright notice in the Description page of Project Settings.


#include "Brokers/FSWorldBroker.h"

#include "Components/WidgetInteractionComponent.h"
#include "Match/FSMatchGameFrameworkBroker.h"
#include "Match/FSMatchUIBroker.h"
#include "Systems/FSGameplayBroker.h"
#include "Utility/FSErrorHandler.h"

void UFSWorldBroker::BindToOtherSubsystems()
{
	// CAPTURING THE SOURCE
	if (UFSMatchGameFrameworkBroker*FrameworkBroker =GetGameFrameworkBroker(GetWorld()))
	{
			FrameworkBroker->OnPlayerJoined.AddDynamic(this, &UFSWorldBroker::HandlePlayerJoined);
			FrameworkBroker->OnPlayerLeft.AddDynamic(this, &UFSWorldBroker::HandlePlayerLeft);
	}
	
	if (UFSMatchUIBroker* MatchUIBroker = GetWorld()->GetSubsystem<UFSMatchUIBroker>())
	{
		// Consume delegate binding
		MatchUIBroker->OnUIItemConsumed.AddDynamic(this, &UFSWorldBroker::HandleOnUIInventoryItemConsumeButtonPressed);
		// Drop delegate binding
		MatchUIBroker->OnUIItemDropped.AddDynamic(this, &UFSWorldBroker::HandleOnUIInventoryItemDropButtonPressed);
	}
	
	if (UFSGameplayBroker* GameplayBroker =GetGameplayBroker(GetWorld()) )
	{
		GameplayBroker->OnInventoryItemAdded.AddDynamic(this, &UFSWorldBroker::HandleInventoryItemAdded);
		GameplayBroker->OnInventoryItemRemoved.AddDynamic(this,&UFSWorldBroker::HandleInventoryItemRemoved);
		GameplayBroker->OnHealthChanged.AddDynamic(this,&UFSWorldBroker::HandleHealthChanged);
		GameplayBroker->OnSanityChanged.AddDynamic(this,&UFSWorldBroker::HandleSanityChanged);
	}
	// Query from gameplay systems
	if (UFSMatchGameFrameworkBroker*FrameworkBroker =GetGameFrameworkBroker(GetWorld()))
	{
		FrameworkBroker->OnGetInventory.BindDynamic(this, &UFSWorldBroker::HandleGetInventory);
		FrameworkBroker->OnHasItem.BindDynamic(this, &UFSWorldBroker::HandleHasItem);
	}
	
	if (UFSMatchUIBroker* MatchUIBroker = GetWorld()->GetSubsystem<UFSMatchUIBroker>())
	{
		MatchUIBroker->OnGetInventory.BindDynamic(this, &UFSWorldBroker::HandleGetInventory);
		MatchUIBroker->OnHasItem.BindDynamic(this, &UFSWorldBroker::HandleHasItem);
	}
	
}

void UFSWorldBroker::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	BindToOtherSubsystems();
	return;
}

void UFSWorldBroker::Deinitialize()
{
	Super::Deinitialize();
	
}

void UFSWorldBroker::HandleInventoryItemAdded(EInventoryItem Item, int Amount)
{
	OnInventoryItemAdded.Broadcast(Item, Amount);
	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnInventoryItemAdded.Broadcast(Item, Amount);
	}
	if (auto* GameFramework = GetGameFrameworkBroker(GetWorld()))
	{
		GameFramework->OnInventoryItemAdded.Broadcast(Item, Amount);
	}
	
}

void UFSWorldBroker::HandleInventoryItemRemoved(EInventoryItem Item, int Amount)
{
	OnInventoryItemRemoved.Broadcast(Item, Amount);
	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnInventoryItemRemoved.Broadcast(Item, Amount);
	}
	if (auto* GameFramework = GetGameFrameworkBroker(GetWorld()))
	{
		GameFramework->OnInventoryItemRemoved.Broadcast(Item, Amount);
	}
}

void UFSWorldBroker::HandleOnUIInventoryItemDropButtonPressed(EInventoryItem Item, int Amount)
{
	OnDropItemButtonPressed.Broadcast(Item,Amount);

	if (UFSGameplayBroker* GameplayBroker =GetGameplayBroker(GetWorld()))
	{
		GameplayBroker->OnDropItemButtonPressed.Broadcast(Item,Amount);
	}
	if (UFSMatchGameFrameworkBroker* FrameworkBroker =GetGameFrameworkBroker(GetWorld()))
	{
		FrameworkBroker->OnDropItemButtonPressed.Broadcast(Item,Amount);
	}
}

void UFSWorldBroker::HandleOnUIInventoryItemConsumeButtonPressed(EInventoryItem Item)
{
	OnConsumeItemButtonPressed.Broadcast(Item);
		
	if (UFSGameplayBroker* GameplayBroker =GetGameplayBroker(GetWorld()))
	{
		GameplayBroker->OnConsumeItemButtonPressed.Broadcast(Item);
	}
	if (UFSMatchGameFrameworkBroker* FrameworkBroker =GetGameFrameworkBroker(GetWorld()))
	{
		FrameworkBroker->OnConsumeItemButtonPressed.Broadcast(Item);
	}
}

void UFSWorldBroker::HandleGetInventory(FInventoryData& EmptyInventory)
{
	if (UFSGameplayBroker* GameplayBroker =GetGameplayBroker(GetWorld()) )
	{
		GameplayBroker->OnGetInventory.ExecuteIfBound(EmptyInventory);

	}

}

void UFSWorldBroker::HandleHasItem(EInventoryItem Item, bool& hasItem)
{
	if (UFSGameplayBroker* GameplayBroker =GetGameplayBroker(GetWorld()) )
	{
		GameplayBroker->OnHasItem.ExecuteIfBound(Item, hasItem);

	}

}
void UFSWorldBroker::HandlePlayerJoined(const FPlayerJoinInfo& Info)
{
	OnPlayerJoined.Broadcast(Info);

	
		if (auto* UI = GetUIBroker(GetWorld()))
		{
			UI->OnUIPlayerJoined.Broadcast(Info);
		}
		
		if (UFSGameplayBroker* GameplayBroker =GetGameplayBroker(GetWorld()))
		{
			GameplayBroker->OnPlayerJoined.Broadcast(Info);
		}
	
		
}

void UFSWorldBroker::HandlePlayerLeft(APlayerState* PS)
{
	OnPlayerLeft.Broadcast(PS);
	if (auto* UI = GetUIBroker(GetWorld()))
	{
			UI->OnUIPlayerLeft.Broadcast(PS);
	}
	if (UFSGameplayBroker* GameplayBroker =GetGameplayBroker(GetWorld()))
	{
		GameplayBroker->OnPlayerLeft.Broadcast(PS);
	}
}

void UFSWorldBroker::HandleSanityChanged(float Percent)
{
	OnSanityChanged.Broadcast(Percent);

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUISanityChanged.Broadcast(Percent);
	}
	

	if (UFSMatchGameFrameworkBroker* FrameworkBroker =GetGameFrameworkBroker(GetWorld()))
	{
		FrameworkBroker->OnFSanityChanged.Broadcast(Percent);
	}
}

void UFSWorldBroker::HandleHealthChanged(float Percent)
{
	OnHealthChanged.Broadcast(Percent);

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUIHealthChanged.Broadcast(Percent);
	}

	if (UFSMatchGameFrameworkBroker* FrameworkBroker =GetGameFrameworkBroker(GetWorld()))
	{
		FrameworkBroker->OnHealthChanged.Broadcast(Percent);
	}
}

void UFSWorldBroker::HandleAnnouncement(const FText& Msg, float Time)
{
	OnAnnouncement.Broadcast(Msg, Time);

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUIAnnouncement.Broadcast(Msg, Time);
	}
}

void UFSWorldBroker::HandleSubtitle(const FText& Msg, float Time)
{
	OnSubtitle.Broadcast(Msg, Time);

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUISubtitle.Broadcast(Msg, Time);
	}
}

void UFSWorldBroker::HandleDiaryShow(const FText& Date, const FText& Body)
{
	OnDiaryShow.Broadcast(Date, Body);

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUIDiaryShow.Broadcast(Date, Body);
	}
}

void UFSWorldBroker::HandleDiaryHide()
{
	OnDiaryHide.Broadcast();

	if (auto* UI = GetUIBroker(GetWorld()))
	{
		UI->OnUIDiaryHide.Broadcast();
	}
}
