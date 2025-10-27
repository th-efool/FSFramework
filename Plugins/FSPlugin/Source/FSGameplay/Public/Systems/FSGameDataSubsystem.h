// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FSGameDataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FSGAMEPLAY_API UFSGameDataSubsystem : public UGameInstanceSubsystem
{
	// THIS CLASS IS FOR STORING ALL THE DATA
	// PLAYER NAME, Total Kills in Game Till Now, History, KD RATION, ETC, ETC
	// WILL PERSIST ACCROSS THEIR PLAY
	GENERATED_BODY()
};
