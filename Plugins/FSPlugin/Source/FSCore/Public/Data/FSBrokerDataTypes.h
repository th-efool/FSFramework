#pragma once
#include "CoreMinimal.h"              // ✅ Required before USTRUCT/UCLASS
#include "GameFramework/PlayerState.h" // If you use APlayerState pointer
#include "FSBrokerDataTypes.generated.h" // ✅ Always include generated header LAST



UENUM(BlueprintType)
enum class  EInventoryItem : uint8
{
	Battery         UMETA(DisplayName = "Battery"),
	SanityPotion    UMETA(DisplayName = "Sanity Potion"),
	HealthPotion    UMETA(DisplayName = "Health Potion"),
	Oil             UMETA(DisplayName = "Oil"),
	KeyA            UMETA(DisplayName = "Key A"),
	KeyB            UMETA(DisplayName = "Key B"),
	KeyC            UMETA(DisplayName = "Key C"),
	KeyD            UMETA(DisplayName = "Key D"),
	KeyE            UMETA(DisplayName = "Key E"),
	KeyF            UMETA(DisplayName = "Key F"),
	KeyG            UMETA(DisplayName = "Key G"),
	AmmoA           UMETA(DisplayName = "Ammo A"),
	AmmoB           UMETA(DisplayName = "Ammo B"),
	AmmoC           UMETA(DisplayName = "Ammo C"),
	AmmoD           UMETA(DisplayName = "Ammo D"),
	AmmoE           UMETA(DisplayName = "Ammo E"),
	ChargeA         UMETA(DisplayName = "Charge A"),
	ChargeB         UMETA(DisplayName = "Charge B"),
	ChargeC         UMETA(DisplayName = "Charge C"),
	ChargeD         UMETA(DisplayName = "Charge D")
};


USTRUCT(BlueprintType)
struct FSCORE_API  FInventoryEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInventoryItem Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Count;
};

USTRUCT(BlueprintType)
struct FSCORE_API FInventoryData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventoryEntry> Entries;

	
	void AddItemToInventory(EInventoryItem Item, uint16 Amount = 1);

	void RemoveItemFromInventory(EInventoryItem Item, uint16 Amount = 1);
	
	uint16 GetItemCount(EInventoryItem Item) const;
	
	bool HasItem(EInventoryItem Item) const;

	// --- Static lookup table for DataTable row names ---
	static const TMap<EInventoryItem, FName>& GetInventoryRowNames()
	{
		static const TMap<EInventoryItem, FName> InventoryRowNames = {
			{EInventoryItem::Battery,      TEXT("Battery")},
			{EInventoryItem::SanityPotion, TEXT("SanityPotion")},
			{EInventoryItem::HealthPotion, TEXT("HealthPotion")},
			{EInventoryItem::Oil,          TEXT("Oil")},

			{EInventoryItem::KeyA, TEXT("KeyA")},
			{EInventoryItem::KeyB, TEXT("KeyB")},
			{EInventoryItem::KeyC, TEXT("KeyC")},
			{EInventoryItem::KeyD, TEXT("KeyD")},
			{EInventoryItem::KeyE, TEXT("KeyE")},
			{EInventoryItem::KeyF, TEXT("KeyF")},
			{EInventoryItem::KeyG, TEXT("KeyG")},

			{EInventoryItem::AmmoA, TEXT("AmmoA")},
			{EInventoryItem::AmmoB, TEXT("AmmoB")},
			{EInventoryItem::AmmoC, TEXT("AmmoC")},
			{EInventoryItem::AmmoD, TEXT("AmmoD")},
			{EInventoryItem::AmmoE, TEXT("AmmoE")},

			{EInventoryItem::ChargeA, TEXT("ChargeA")},
			{EInventoryItem::ChargeB, TEXT("ChargeB")},
			{EInventoryItem::ChargeC, TEXT("ChargeC")},
			{EInventoryItem::ChargeD, TEXT("ChargeD")},
		};
		return InventoryRowNames;
	}

	static FName GetRowName(EInventoryItem Item)
	{
		const auto& Map = GetInventoryRowNames();
		if (const FName* Found = Map.Find(Item))
			return *Found;

		return NAME_None; // Safe fallback if enum isn’t mapped
	}
};


USTRUCT(BlueprintType)
struct FSCORE_API  FPlayerJoinInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<APlayerState> PlayerState = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bIsLocalPlayer = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerJoinedSignature, const FPlayerJoinInfo&, Info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerLeftSignature, APlayerState*, PlayerState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSanityChangedSignature, float, SanityPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChangedSignature, float, HealthPercent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAnnouncementSignature, const FText&, Message, float, Time);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSubtitleSignature, const FText&, Message, float, Time);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDiaryShowSignature, const FText&, Date, const FText&, Body);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDiaryHideSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FInventoryItemAddedSignature,
	EInventoryItem, ItemType,
	int, Amount
);

// Called when an item is removed from the inventory.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FInventoryItemRemovedSignature,
	EInventoryItem, ItemType,
	int, Amount
);

// Called when the full inventory needs to be sent or updated.
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetInventory, FInventoryData&, Inventory);
