#include "FSBrokerDataTypes.h"

void FInventoryData::AddItemToInventory(EInventoryItem Item, uint16 Amount)
{
	if (Amount == 0)
		return;

	for (FInventoryEntry& Entry : Entries)
	{
		if (Entry.Item == Item)
		{
			Entry.Count += Amount;
			return;
		}
	}

	// If not found, add new entry
	FInventoryEntry NewEntry;
	NewEntry.Item = Item;
	NewEntry.Count = Amount;
	Entries.Add(NewEntry);
}

void FInventoryData::RemoveItemFromInventory(EInventoryItem Item, uint16 Amount)
{
	if (Amount == 0)
		return;

	for (int32 i = 0; i < Entries.Num(); ++i)
	{
		if (Entries[i].Item == Item)
		{
			if (Entries[i].Count <= Amount)
			{
				Entries.RemoveAt(i);
			}
			else
			{
				Entries[i].Count -= Amount;
			}
			return;
		}
	}
}

uint16 FInventoryData::GetItemCount(EInventoryItem Item) const
{
	for (const FInventoryEntry& Entry : Entries)
	{
		if (Entry.Item == Item)
			return Entry.Count;
	}
	return 0;
}

bool FInventoryData::HasItem(EInventoryItem Item) const
{
	for (const FInventoryEntry& Entry : Entries)
	{
		if (Entry.Item == Item)
			return true;
	}
	return false;
}
