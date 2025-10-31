// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FSBrokerDataTypes.h"
#include "Base/FSComponentWidgetBase.h"
#include "FSInventory.generated.h"

namespace InventoryRowNames
{
	static const FName Battery      = TEXT("Battery");
	static const FName SanityPotion = TEXT("SanityPotion");
	static const FName HealthPotion = TEXT("HealthPotion");
	static const FName Oil          = TEXT("Oil");

	static const FName KeyA = TEXT("KeyA");
	static const FName KeyB = TEXT("KeyB");
	static const FName KeyC = TEXT("KeyC");
	static const FName KeyD = TEXT("KeyD");
	static const FName KeyE = TEXT("KeyE");
	static const FName KeyF = TEXT("KeyF");
	static const FName KeyG = TEXT("KeyG");

	static const FName AmmoA = TEXT("AmmoA");
	static const FName AmmoB = TEXT("AmmoB");
	static const FName AmmoC = TEXT("AmmoC");
	static const FName AmmoD = TEXT("AmmoD");
	static const FName AmmoE = TEXT("AmmoE");

	static const FName ChargeA = TEXT("ChargeA");
	static const FName ChargeB = TEXT("ChargeB");
	static const FName ChargeC = TEXT("ChargeC");
	static const FName ChargeD = TEXT("ChargeD");
}

USTRUCT(BlueprintType)
struct FSUI_API FFSInventoryItemRow : public FTableRowBase
{
	GENERATED_BODY()

	/** Item type (must match DataTable row name or Enum value) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	EInventoryItem Item = EInventoryItem::Battery;

	/** Icon or texture representing the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSoftObjectPtr<UTexture2D> ItemIcon;

	/** Description text shown in inventory UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FText Description;

	/** Default quantity (for pickup or stack size) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 DefaultQuantity = 1;

	/** Actor or item class reference (e.g., pickup, consumable actor, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<AActor> ItemActorClass;
};

UCLASS()
class FSUI_API UFSInventory : public UFSComponentWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> InventoryTable;

	

};
