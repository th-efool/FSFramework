// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/Components/FSInventoryItemWidget.h"

// FSInventoryItemWidget.cpp

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Match/FSMatchUIBroker.h"
#include "Utility/FSErrorHandler.h"

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
	if (DropButton)
	{
		DropAmountSpinBox->SetMinValue(1);
		DropAmountSpinBox->SetMaxValue(InQuantity);
	}
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
	DropAmountSpinBox->SetMaxValue(QuantityCount);

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
	DropAmountSpinBox->SetMaxValue(QuantityCount);
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
	auto world = GetWorld();
	if (!world) return;
	UFSMatchUIBroker* broker = world->GetSubsystem<UFSMatchUIBroker>();
	if (!broker) return;
	broker->OnUIItemDropped.Broadcast(ItemType,DropAmountSpinBox->GetValue());
	FS_PRINT_SCREEN("UIBroker: ITEM WAS DROPPED");
	FS_PRINT_SCREEN(FString::Printf(TEXT("Dropped Amount: %.0f"), DropAmountSpinBox->GetValue()));


}

void UFSInventoryItemWidget::OnConsumeClicked()
{
	if (!bConsumable)
		return;

	auto world = GetWorld();
	if (!world) return;
	UFSMatchUIBroker* broker = world->GetSubsystem<UFSMatchUIBroker>();
	if (!broker) return;
	broker->OnUIItemConsumed.Broadcast(ItemType);
		
}

