// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/Components/FSInventory.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "Subsystems/WorldSubsystem.h"
#include "DataTableEditorUtils.h"
#include "Match/FSMatchUIBroker.h"

#include "Engine/DataTable.h"

// --- PopulateInventory: now minimal, delegates heavy lifting to CustomAddEntry
void UFSInventory::PopulateInventory()
{
	if (!InventoryTable || !ItemWidgetClass || !VerticalBox_Items)
		return;

	FInventoryData UninitializedInventory;
	if (auto* Broker = GetWorld()->GetSubsystem<UFSMatchUIBroker>())
	{
		Broker->OnGetInventory.ExecuteIfBound(UninitializedInventory);
	}

	if (UninitializedInventory.Entries.IsEmpty())
		return;

	for (const FInventoryEntry& Entry : UninitializedInventory.Entries)
	{
		CustomAddEntry(Entry);
	}
}

// --- Adds items for a single FInventoryEntry: merges into existing widgets or creates new ones,
//     splitting by MaxBatchSize from metadata.
void UFSInventory::CustomAddEntry(const FInventoryEntry& Entry)
{
	if (!InventoryTable || !ItemWidgetClass || !VerticalBox_Items)
		return;

	static const FString Context(TEXT("InventoryLookup"));

	// Map enum -> row name (explicit switch using your InventoryRowNames namespace)
	const FName* RowNamePtr = nullptr;
	switch (Entry.Item)
	{
	case EInventoryItem::Battery:         RowNamePtr = &InventoryRowNames::Battery; break;
	case EInventoryItem::SanityPotion:    RowNamePtr = &InventoryRowNames::SanityPotion; break;
	case EInventoryItem::HealthPotion:    RowNamePtr = &InventoryRowNames::HealthPotion; break;
	case EInventoryItem::Oil:             RowNamePtr = &InventoryRowNames::Oil; break;
	case EInventoryItem::KeyA:            RowNamePtr = &InventoryRowNames::KeyA; break;
	case EInventoryItem::KeyB:            RowNamePtr = &InventoryRowNames::KeyB; break;
	case EInventoryItem::KeyC:            RowNamePtr = &InventoryRowNames::KeyC; break;
	case EInventoryItem::KeyD:            RowNamePtr = &InventoryRowNames::KeyD; break;
	case EInventoryItem::KeyE:            RowNamePtr = &InventoryRowNames::KeyE; break;
	case EInventoryItem::KeyF:            RowNamePtr = &InventoryRowNames::KeyF; break;
	case EInventoryItem::KeyG:            RowNamePtr = &InventoryRowNames::KeyG; break;
	case EInventoryItem::AmmoA:           RowNamePtr = &InventoryRowNames::AmmoA; break;
	case EInventoryItem::AmmoB:           RowNamePtr = &InventoryRowNames::AmmoB; break;
	case EInventoryItem::AmmoC:           RowNamePtr = &InventoryRowNames::AmmoC; break;
	case EInventoryItem::AmmoD:           RowNamePtr = &InventoryRowNames::AmmoD; break;
	case EInventoryItem::AmmoE:           RowNamePtr = &InventoryRowNames::AmmoE; break;
	case EInventoryItem::ChargeA:         RowNamePtr = &InventoryRowNames::ChargeA; break;
	case EInventoryItem::ChargeB:         RowNamePtr = &InventoryRowNames::ChargeB; break;
	case EInventoryItem::ChargeC:         RowNamePtr = &InventoryRowNames::ChargeC; break;
	case EInventoryItem::ChargeD:         RowNamePtr = &InventoryRowNames::ChargeD; break;
	default:
		return;
	}

	const FFSInventoryItemRow* MetaRow = InventoryTable->FindRow<FFSInventoryItemRow>(*RowNamePtr, Context);
	if (!MetaRow)
		return;

	const int32 MaxBatch = FMath::Max(1, MetaRow->MaxBatchSize);
	int32 Remaining = Entry.Count;

	// First: fill existing widgets that have space
	while (Remaining > 0)
	{
		UFSInventoryItemWidget* WidgetWithSpace = FindWidgetWithSpace(Entry.Item, MaxBatch);
		if (!WidgetWithSpace)
			break;

		int32 Space = MaxBatch - WidgetWithSpace->GetQuantity();
		int32 ToAdd = FMath::Min(Space, Remaining);
		if (ToAdd > 0)
		{
			WidgetWithSpace->IncrementQuantity(ToAdd);
			Remaining -= ToAdd;
		}
		else
		{
			// Defensive: avoid infinite loop if widget reports full despite FindWidgetWithSpace
			break;
		}
	}

	// Second: create new widgets (split into batches of MaxBatch)
	while (Remaining > 0)
	{
		int32 BatchSize = FMath::Min(Remaining, MaxBatch);
		UFSInventoryItemWidget* NewWidget = CreateInventoryItemWidget(Entry.Item, BatchSize);
		if (NewWidget && VerticalBox_Items)
		{
			VerticalBox_Items->AddChildToVerticalBox(NewWidget);
			Remaining -= BatchSize;
		}
		else
		{
			// If creation fails, stop to avoid infinite loop
			break;
		}
	}
}

// --- Search vertical box for a widget of ItemType with quantity < MaxBatch
UFSInventoryItemWidget* UFSInventory::FindWidgetWithSpace(EInventoryItem ItemType, int MaxBatch) const
{
	if (!VerticalBox_Items)
		return nullptr;

	const int32 Count = VerticalBox_Items->GetChildrenCount();
	for (int32 i = 0; i < Count; ++i)
	{
		UWidget* Child = VerticalBox_Items->GetChildAt(i);
		if (!Child) continue;

		if (UFSInventoryItemWidget* ItemWidget = Cast<UFSInventoryItemWidget>(Child))
		{
			const int32 CurrentQuantity = FCString::Atoi(*ItemWidget->Quantity->GetText().ToString());

			if (ItemWidget->ItemType == ItemType && CurrentQuantity < MaxBatch)
			{
				// Add to this stack instead of creating a new one
				const int32 NewQuantity = FMath::Min(CurrentQuantity + Entry.Quantity, MaxBatch);
				ItemWidget->Quantity->SetText(FText::AsNumber(NewQuantity));
			}
		}
		
	}
	return nullptr;
}

// --- Create a widget and initialize with destructured params (uses meta row lookup internally)
UFSInventoryItemWidget* UFSInventory::CreateInventoryItemWidget(EInventoryItem ItemType, int Amount)
{
	if (!InventoryTable || !ItemWidgetClass)
		return nullptr;

	static const FString Context(TEXT("InventoryLookup"));

	const FName* RowNamePtr = nullptr;
	switch (ItemType)
	{
	case EInventoryItem::Battery:         RowNamePtr = &InventoryRowNames::Battery; break;
	case EInventoryItem::SanityPotion:    RowNamePtr = &InventoryRowNames::SanityPotion; break;
	case EInventoryItem::HealthPotion:    RowNamePtr = &InventoryRowNames::HealthPotion; break;
	case EInventoryItem::Oil:             RowNamePtr = &InventoryRowNames::Oil; break;
	case EInventoryItem::KeyA:            RowNamePtr = &InventoryRowNames::KeyA; break;
	case EInventoryItem::KeyB:            RowNamePtr = &InventoryRowNames::KeyB; break;
	case EInventoryItem::KeyC:            RowNamePtr = &InventoryRowNames::KeyC; break;
	case EInventoryItem::KeyD:            RowNamePtr = &InventoryRowNames::KeyD; break;
	case EInventoryItem::KeyE:            RowNamePtr = &InventoryRowNames::KeyE; break;
	case EInventoryItem::KeyF:            RowNamePtr = &InventoryRowNames::KeyF; break;
	case EInventoryItem::KeyG:            RowNamePtr = &InventoryRowNames::KeyG; break;
	case EInventoryItem::AmmoA:           RowNamePtr = &InventoryRowNames::AmmoA; break;
	case EInventoryItem::AmmoB:           RowNamePtr = &InventoryRowNames::AmmoB; break;
	case EInventoryItem::AmmoC:           RowNamePtr = &InventoryRowNames::AmmoC; break;
	case EInventoryItem::AmmoD:           RowNamePtr = &InventoryRowNames::AmmoD; break;
	case EInventoryItem::AmmoE:           RowNamePtr = &InventoryRowNames::AmmoE; break;
	case EInventoryItem::ChargeA:         RowNamePtr = &InventoryRowNames::ChargeA; break;
	case EInventoryItem::ChargeB:         RowNamePtr = &InventoryRowNames::ChargeB; break;
	case EInventoryItem::ChargeC:         RowNamePtr = &InventoryRowNames::ChargeC; break;
	case EInventoryItem::ChargeD:         RowNamePtr = &InventoryRowNames::ChargeD; break;
	default:
		return nullptr;
	}

	const FFSInventoryItemRow* MetaRow = InventoryTable->FindRow<FFSInventoryItemRow>(*RowNamePtr, Context);
	if (!MetaRow)
		return nullptr;

	UFSInventoryItemWidget* ItemWidget = CreateWidget<UFSInventoryItemWidget>(GetWorld(), ItemWidgetClass);
	if (!ItemWidget)
		return nullptr;

	ItemWidget->SetupItem(
		ItemType,
		MetaRow->ItemIcon.LoadSynchronous(),  // synchronous icon load for UI setup
		MetaRow->Description,
		Amount,
		MetaRow->IsConsumeable,
		MetaRow->ItemActorClass
	);

	return ItemWidget;
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


void UFSInventory::HandleItemAdded(EInventoryItem ItemType, int Amount)
{
	// Find if item widget already exists
	if (!VerticalBox_Items)
		return;

	// Try to find an existing widget representing this item type
	for (UWidget* Child : VerticalBox_Items->GetAllChildren())
	{
		if (auto* ItemWidget = Cast<UFSInventoryItemWidget>(Child))
		{
			if (ItemWidget->ItemType == ItemType)
			{
				ItemWidget->IncrementQuantity(Amount);
				return;
			}
		}
	}

	// If not found, create a new one
	AddNewItemWidget(ItemType, Amount);
}

void UFSInventory::HandleItemRemoved(EInventoryItem ItemType, int Amount)
{
	if (!VerticalBox_Items)
		return;

	for (int32 i = VerticalBox_Items->GetChildrenCount() - 1; i >= 0; --i)
	{
		if (auto* ItemWidget = Cast<UFSInventoryItemWidget>(VerticalBox_Items->GetChildAt(i)))
		{
			if (ItemWidget->ItemType == ItemType)
			{
				ItemWidget->DecrementQuantity(Amount);

				if (ItemWidget->GetQuantity() <= 0)
					VerticalBox_Items->RemoveChildAt(i);

				return;
			}
		}
	}
}

