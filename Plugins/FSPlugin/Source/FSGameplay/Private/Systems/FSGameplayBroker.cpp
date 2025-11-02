// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/FSGameplayBroker.h"
#include "Kismet/GameplayStatics.h"
#include "Systems/Interface/FSFlicker.h"

void UFSGameplayBroker::RelayInventoryItemAdded(EInventoryItem Item, int Amount)
{
	OnInventoryItemAdded.Broadcast(Item,Amount);
}

void UFSGameplayBroker::RelayInventoryItemRemoved(EInventoryItem Item, int Amount)
{
	OnInventoryItemRemoved.Broadcast(Item,Amount);
}

void UFSGameplayBroker::RelayGetInventory(FInventoryData& Inventory)
{
	OnGetInventory.ExecuteIfBound(Inventory);
}

bool UFSGameplayBroker::HasItem(EInventoryItem Item)
{
	bool ResultValue=false;
	OnHasItem.ExecuteIfBound(Item, ResultValue);
	return ResultValue;
}
