// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Interactables/InteractableActorBase.h"


// Sets default values
AInteractableActorBase::AInteractableActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AInteractableActorBase::Interact_Implementation(AActor* InteractionInstigator)
{
	IFSInteract::Interact_Implementation(InteractionInstigator);
	
}

// Called when the game starts or when spawned
void AInteractableActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

