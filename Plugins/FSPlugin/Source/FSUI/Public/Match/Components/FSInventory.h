// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FSBrokerDataTypes.h"
#include "Match/Components/FSInventoryItemWidget.h"
#include "Base/FSComponentWidgetBase.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "FSInventory.generated.h"



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

	/** Default quantity (for pickup or stack size) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxBatchSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool IsConsumeable=false;

	/** Actor or item class reference (e.g., pickup, consumable actor, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<AActor> ItemActorClass;
};

UCLASS()
class FSUI_API UFSInventory : public UFSComponentWidgetBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FSInventory")
	TSoftObjectPtr<UDataTable> InventoryTable;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ScrollBox_Inventory = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Items = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FSInventory")
	TSubclassOf<UFSInventoryItemWidget> ItemWidgetClass;
public:
	void PopulateInventory();

private:
	UFUNCTION()
	void HandleItemAdded(EInventoryItem ItemType, int Amount);

	UFUNCTION()
	void HandleItemRemoved(EInventoryItem ItemType, int Amount);

public:
	virtual void NativeConstruct() override;
	void NativeDestruct();

	// Shared helper that creates a widget from metadata.
	UFSInventoryItemWidget* CreateInventoryItemWidget(const FFSInventoryItemRow& Row, EInventoryItem ItemType, int32 Quantity);

	// Called per FInventoryEntry to split into batches and merge into existing widgets.
	void AddInventoryEntry(const FInventoryEntry& Entry);

	// Find an existing item widget that has space to accept more of ItemType (returns nullptr if none).
	UFSInventoryItemWidget* FindWidgetWithSpace(EInventoryItem ItemType, int MaxBatch) const;


	
};
