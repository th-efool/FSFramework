// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FSCharacterBase.h"

#include "Systems/FSGameplayBroker.h"
#include "Utility/FSErrorHandler.h"


// Sets default values
AFSCharacterBase::AFSCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AFSCharacterBase::HandleItemAdded(EInventoryItem Item, int Count)
{
	InventoryPlayer.AddItemToInventory(Item, Count);
}

void AFSCharacterBase::HandleItemRemoved(EInventoryItem Item, int Count)
{
	InventoryPlayer.RemoveItemFromInventory(Item, Count);
}

void AFSCharacterBase::HandleGetInventory(FInventoryData& EmptyInventory)
{
	EmptyInventory = InventoryPlayer;
}

void AFSCharacterBase::DropItem_Implementation(EInventoryItem Item, int32 Count)
{
	UFSGameplayBroker* broker = GetWorld()->GetSubsystem<UFSGameplayBroker>();
	if (!broker){return;}
	broker->OnInventoryItemRemoved.Broadcast(Item, Count);
}



void AFSCharacterBase::ConsumeItem_Implementation(EInventoryItem Item)
{
	UFSGameplayBroker* broker = GetWorld()->GetSubsystem<UFSGameplayBroker>();
	if (!broker){return;}
	broker->OnInventoryItemRemoved.Broadcast(Item,1);

}


// Called every frame
void AFSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
// Called to bind functionality to input
void AFSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AFSCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsLocallyControlled())
	{
		InitializeLocalBindings();
	}
}

void AFSCharacterBase::InitializeLocalBindings()
{
	UFSGameplayBroker* broker = GetWorld()->GetSubsystem<UFSGameplayBroker>();
	if (!broker){return;}
	
		broker->OnInventoryItemAdded.AddDynamic(this, &AFSCharacterBase::HandleItemAdded);
		broker->OnInventoryItemRemoved.AddDynamic(this, &AFSCharacterBase::HandleItemRemoved);
		broker->OnGetInventory.BindDynamic(this, &AFSCharacterBase::HandleGetInventory);
		broker->OnDropItemButtonPressed.AddDynamic(this,&AFSCharacterBase::DropItem);
		broker->OnConsumeItemButtonPressed.AddDynamic(this,&AFSCharacterBase::ConsumeItem);
}

void AFSCharacterBase::UnPossessed()
{
	Super::UnPossessed();
	UnbindInventoryDelegates();
}

void AFSCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnbindInventoryDelegates();
}

void AFSCharacterBase::UnbindInventoryDelegates()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UFSGameplayBroker* Broker = World->GetSubsystem<UFSGameplayBroker>();
	if (!Broker) return;

	Broker->OnInventoryItemAdded.RemoveDynamic(this, &AFSCharacterBase::HandleItemAdded);
	Broker->OnInventoryItemRemoved.RemoveDynamic(this, &AFSCharacterBase::HandleItemRemoved);

	// For single-cast dynamic delegate:
	if (Broker->OnGetInventory.IsBound())
	{
		Broker->OnGetInventory.Unbind();
	}
}
