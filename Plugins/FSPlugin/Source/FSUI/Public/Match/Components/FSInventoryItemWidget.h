// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FSComponentWidgetBase.h"
#include "Blueprint/UserWidget.h"
#include "Data/FSBrokerDataTypes.h"
#include "Components/SpinBox.h"

#include "FSInventoryItemWidget.generated.h"


class UButton;
class UTextBlock;
class UImage;

UCLASS()
class FSUI_API UFSInventoryItemWidget : public UFSComponentWidgetBase
{
	GENERATED_BODY()

public:
	EInventoryItem ItemType;
	TSubclassOf<AActor> ItemActorClass;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UImage> ItemIcon = nullptr;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> ItemName = nullptr;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> Description = nullptr;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> Quantity = nullptr;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<class USpinBox> DropAmountSpinBox = nullptr;

	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> DropButton = nullptr;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> ConsumeButton = nullptr;

public:
	void SetupItem(
		EInventoryItem InItemType,
		UTexture2D* InItemIcon,
		const FText& InDescription,
		int32 InQuantity,
		bool bIsConsumable,
		TSubclassOf<AActor> InActorClass
	);

	int32 GetQuantity() const;
	void IncrementQuantity(int32 Amount);
	void DecrementQuantity(int32 Amount);


protected:
	virtual void NativeConstruct() override;

	UFUNCTION() void OnDropClicked();
	UFUNCTION() void OnConsumeClicked();

private:

	bool bConsumable = false;
	int32 QuantityCount = 0;
};
