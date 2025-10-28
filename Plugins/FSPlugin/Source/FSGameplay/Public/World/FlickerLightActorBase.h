// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Systems/Interface/FSFlicker.h"
#include "Components/PointLightComponent.h"

#include "FlickerLightActorBase.generated.h"

UCLASS()
class FSGAMEPLAY_API AFlickerLightActorBase : public AActor, public IFSFlicker
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlickerLightActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPointLightComponent* PointLight;

	FTimerHandle FlickerTimerHandle;

public:
	// Flicker implementation
	virtual void Flicker_Implementation(float Duration) override;

private:
	void ToggleLight();
};
