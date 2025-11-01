// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/Components/FSInventoryItemWidget.h"

// FSInventoryItemWidget.cpp

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UFSInventoryItemWidget::SetupItem(
	EInventoryItem InItemType,
	UTexture2D* InItemIcon,
	const FText& InDescription,
	int32 InQuantity,
	bool bIsConsumable,
	TSubclassOf<AActor> InActorClass
)
{
	ItemType = InItemType;
	ItemActorClass = InActorClass;
	bConsumable = bIsConsumable;
	QuantityCount = InQuantity;

	if (ItemIcon) ItemIcon->SetBrushFromTexture(InItemIcon);
	if (ItemName) ItemName->SetText(FText::FromString(UEnum::GetValueAsString(InItemType)));
	if (Description) Description->SetText(InDescription);
	if (Quantity) Quantity->SetText(FText::AsNumber(InQuantity));

	if (ConsumeButton)
		ConsumeButton->SetIsEnabled(bIsConsumable);
}

int32 UFSInventoryItemWidget::GetQuantity() const
{
	return QuantityCount;
}

void UFSInventoryItemWidget::IncrementQuantity(int32 Amount)
{
	if (Amount <= 0)
		return;

	QuantityCount += Amount;

	if (Quantity)
	{
		Quantity->SetText(FText::AsNumber(QuantityCount));
	}
}

void UFSInventoryItemWidget::DecrementQuantity(int32 Amount)
{
	if (Amount <= 0)
		return;

	QuantityCount = FMath::Max(QuantityCount - Amount, 0);

	if (Quantity)
	{
		Quantity->SetText(FText::AsNumber(QuantityCount));
	}
}


void UFSInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DropButton)
		DropButton->OnClicked.AddDynamic(this, &UFSInventoryItemWidget::OnDropClicked);
	if (ConsumeButton)
		ConsumeButton->OnClicked.AddDynamic(this, &UFSInventoryItemWidget::OnConsumeClicked);
}

void UFSInventoryItemWidget::OnDropClicked()
{
	// TODO: Implement drop logic (emit event)
}

void UFSInventoryItemWidget::OnConsumeClicked()
{
	if (!bConsumable)
		return;

	// TODO: Implement consume logic (emit event)
}
