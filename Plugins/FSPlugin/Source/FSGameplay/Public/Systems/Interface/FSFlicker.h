// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FSFlicker.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UFSFlicker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FSGAMEPLAY_API IFSFlicker
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Flicker(float Duration);
	virtual void Flicker_Implementation(float Duration){}
	
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetIntensityFlicker(float Intensity);
	virtual void SetIntensityFlicker_Implementation(float Intensity){}
	
};
