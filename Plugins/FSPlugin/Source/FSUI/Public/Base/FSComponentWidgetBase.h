// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSUserWidgetBase.h"
#include "FSComponentWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class FSUI_API UFSComponentWidgetBase : public UFSUserWidgetBase
{
	GENERATED_BODY()
public:
	float showElapsed = 0.f;
	float showDuration = 0.f;
	float fadeDuration = 0.f;

	FTimerHandle showTimerHandle;
};
