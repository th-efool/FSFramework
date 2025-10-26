// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FSInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UFSInteract : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FSGAMEPLAY_API IFSInteract
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(AActor* InteractionInstigator);

	virtual void Interact_Implementation(AActor* InteractionInstigator) {}
};
