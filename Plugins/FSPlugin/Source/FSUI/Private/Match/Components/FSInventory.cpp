// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/Components/FSInventory.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "Subsystems/WorldSubsystem.h"
#include "DataTableEditorUtils.h"
#include "Match/FSMatchUIBroker.h"

#include "Engine/DataTable.h"
#include "Utility/FSErrorHandler.h"

void UFSInventory::PopulateInventory()
{
	if (!InventoryTable || !ItemWidgetClass || !VerticalBox_Items)
		return;

	FInventoryData Inventory;
	if (auto* Broker = GetWorld()->GetSubsystem<UFSMatchUIBroker>())
		Broker->OnGetInventory.ExecuteIfBound(Inventory);

	if (Inventory.Entries.IsEmpty())
		return;

	for (const FInventoryEntry& Entry : Inventory.Entries)
		AddInventoryEntry(Entry);
}

// ------------------------------------------------------------
// AddInventoryEntry — handles merging / batching / widget spawn
// ------------------------------------------------------------
void UFSInventory::AddInventoryEntry(const FInventoryEntry& Entry)
{
	if (!InventoryTable || !ItemWidgetClass || !VerticalBox_Items)
		return;

	static const FString Context(TEXT("InventoryLookup"));
	const FName RowName = FInventoryData::GetRowName(Entry.Item);
	if (RowName.IsNone())
		return;

	const FFSInventoryItemRow* Row = InventoryTable->FindRow<FFSInventoryItemRow>(RowName, Context);
	if (!Row)
		return;

	const int32 MaxBatch = FMath::Max(1, Row->MaxBatchSize);
	int32 Remaining = Entry.Count;

	// Fill partially-filled stacks first
	while (Remaining > 0)
	{
		if (UFSInventoryItemWidget* Widget = FindWidgetWithSpace(Entry.Item, MaxBatch))
		{
			const int32 FreeSpace = MaxBatch - Widget->GetQuantity();
			const int32 ToAdd = FMath::Min(FreeSpace, Remaining);
			if (ToAdd <= 0)
				break;

			Widget->IncrementQuantity(ToAdd);
			Remaining -= ToAdd;
			continue;
		}
		break; // none found
	}

	// Create new stacks as needed
	while (Remaining > 0)
	{
		const int32 BatchSize = FMath::Min(Remaining, MaxBatch);
		if (UFSInventoryItemWidget* NewWidget = CreateInventoryItemWidget(*Row, Entry.Item, BatchSize))
		{
			VerticalBox_Items->AddChildToVerticalBox(NewWidget);
			Remaining -= BatchSize;
		}
		else break; // creation failure
	}
}

// ------------------------------------------------------------
// Finds a widget with same type and remaining capacity
// ------------------------------------------------------------
UFSInventoryItemWidget* UFSInventory::FindWidgetWithSpace(EInventoryItem ItemType, int32 MaxBatch) const
{
	if (!VerticalBox_Items)
		return nullptr;

	const int32 Count = VerticalBox_Items->GetChildrenCount();
	for (int32 i = 0; i < Count; ++i)
	{
		if (auto* Widget = Cast<UFSInventoryItemWidget>(VerticalBox_Items->GetChildAt(i)))
			if (Widget->ItemType == ItemType && Widget->GetQuantity() < MaxBatch)
				return Widget;
	}
	return nullptr;
}

// ------------------------------------------------------------
// Creates and initializes a widget from metadata row
// ------------------------------------------------------------

UFSInventoryItemWidget* UFSInventory::CreateInventoryItemWidget(const FFSInventoryItemRow& Row, EInventoryItem ItemType, int32 Quantity)
{
	if (!ItemWidgetClass)
		return nullptr;

	UFSInventoryItemWidget* Widget = CreateWidget<UFSInventoryItemWidget>(GetWorld(), ItemWidgetClass);
	if (!Widget)
		return nullptr;

	// Destructure from DataTable row directly
	Widget->SetupItem(
		ItemType,
		Row.ItemIcon.LoadSynchronous(),
		Row.Description,
		Quantity,
		Row.IsConsumeable,
		Row.ItemActorClass
	);

	return Widget;
}



void UFSInventory::HandleItemAdded(EInventoryItem ItemType, int Amount)
{

	if (!VerticalBox_Items || !InventoryTable || !ItemWidgetClass)
		return;

	const FName RowName = FInventoryData::GetRowName(ItemType);
	if (RowName.IsNone())
		return;

	static const FString Context(TEXT("InventoryLookup"));
	const FFSInventoryItemRow* Row = InventoryTable->FindRow<FFSInventoryItemRow>(RowName, Context);
	if (!Row)
		return;

	const int32 MaxBatch = FMath::Max(1, Row->MaxBatchSize);
	int32 Remaining = Amount;

	// Fill existing stacks first
	while (Remaining > 0)
	{
		UFSInventoryItemWidget* Stack = FindWidgetWithSpace(ItemType, MaxBatch);
		if (!Stack)
			break;

		const int32 FreeSpace = MaxBatch - Stack->GetQuantity();
		const int32 ToAdd = FMath::Min(FreeSpace, Remaining);
		if (ToAdd <= 0)
			break;

		Stack->IncrementQuantity(ToAdd);
		Remaining -= ToAdd;
	}

	// Create new stacks for leftover amount
	while (Remaining > 0)
	{
		const int32 BatchSize = FMath::Min(Remaining, MaxBatch);
		if (UFSInventoryItemWidget* NewWidget = CreateInventoryItemWidget(*Row, ItemType, BatchSize))
		{
			VerticalBox_Items->AddChildToVerticalBox(NewWidget);
			Remaining -= BatchSize;
		}
		else break;
	}
}




void UFSInventory::HandleItemRemoved(EInventoryItem ItemType, int Amount)
{
	if (!VerticalBox_Items)
		return;

	int32 Remaining = Amount;

	// Iterate backwards to safely remove
	for (int32 i = VerticalBox_Items->GetChildrenCount() - 1; i >= 0 && Remaining > 0; --i)
	{
		if (auto* Widget = Cast<UFSInventoryItemWidget>(VerticalBox_Items->GetChildAt(i)))
		{
			if (Widget->ItemType != ItemType)
				continue;

			const int32 Current = Widget->GetQuantity();
			const int32 ToRemove = FMath::Min(Current, Remaining);

			Widget->DecrementQuantity(ToRemove);
			Remaining -= ToRemove;

			if (Widget->GetQuantity() <= 0)
				VerticalBox_Items->RemoveChildAt(i);
		}
	}
}


void UFSInventory::NativeConstruct()
{
	Super::NativeConstruct();

	if (UWorld* World = GetWorld())
	{
		if (UFSMatchUIBroker* Broker = World->GetSubsystem<UFSMatchUIBroker>())
		{
			Broker->OnInventoryItemAdded.AddDynamic(this, &UFSInventory::HandleItemAdded);
			Broker->OnInventoryItemRemoved.AddDynamic(this, &UFSInventory::HandleItemRemoved);
		}
	}

	// Optionally populate initial inventory
	PopulateInventory();
}
void UFSInventory::NativeDestruct()
{
	if (UWorld* World = GetWorld())
	{
		if (UFSMatchUIBroker* Broker = World->GetSubsystem<UFSMatchUIBroker>())
		{
			Broker->OnInventoryItemAdded.RemoveDynamic(this, &UFSInventory::HandleItemAdded);
			Broker->OnInventoryItemRemoved.RemoveDynamic(this, &UFSInventory::HandleItemRemoved);
		}
	}

	Super::NativeDestruct();
}

