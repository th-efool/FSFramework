// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FSBrokerDataTypes.h"
#include "GameFramework/Character.h"
#include "FSCharacterBase.generated.h"

UCLASS()
class FSGAMEPLAY_API AFSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFSCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	virtual void PossessedBy(AController* NewController) override;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FInventoryData getInventory(){return InventoryPlayer;}
private:
	FInventoryData InventoryPlayer;
	void InitializeLocalBindings();
	virtual void UnPossessed() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	void UnbindInventoryDelegates();

	UFUNCTION()
	void HandleItemAdded(EInventoryItem Item, int Count);
	UFUNCTION()
	void HandleItemRemoved(EInventoryItem Item, int Count);
	UFUNCTION()
	void HandleGetInventory(FInventoryData& EmptyInventory);
	UFUNCTION()
	void HandleHasItem(EInventoryItem Item, bool& hasItem);
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void DropItem(EInventoryItem Item, int32 Count);

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void ConsumeItem(EInventoryItem Item);

	UFUNCTION(BlueprintCallable)
	bool HasItem(EInventoryItem Item);
	

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
