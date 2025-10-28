// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Systems/Interface/FSInteract.h"
#include "InteractableActorBase.generated.h"

UCLASS()
class FSGAMEPLAY_API AInteractableActorBase : public AActor, public IFSInteract
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableActorBase();
	virtual void Interact_Implementation(AActor* InteractionInstigator) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
