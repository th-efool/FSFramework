// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSPlayerCharacterBase.h"
#include "FSFPSPlayerCharacter.generated.h"

UCLASS()
class FSGAMEPLAY_API AFSFPSPlayerCharacter : public AFSPlayerCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFSFPSPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Camera Sway
public:
	virtual void DoLook(float Yaw, float Pitch) override;
	UPROPERTY()
	float Tilt=0.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxTilt=3.0f;
	UPROPERTY(EditDefaultsOnly)
	float TiltRecoverySpeed=9.0f;
};
