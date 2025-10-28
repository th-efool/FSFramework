// Fill out your copyright notice in the Description page of Project Settings.


#include "World/FlickerLightActorBase.h"
#include "TimerManager.h"


// Sets default values
AFlickerLightActorBase::AFlickerLightActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	RootComponent = PointLight;
}

// Called when the game starts or when spawned
void AFlickerLightActorBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFlickerLightActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AFlickerLightActorBase::Flicker_Implementation(float Duration)
{
	constexpr float FlickerInterval = 0.1f;
	GetWorldTimerManager().SetTimer(FlickerTimerHandle, this, &AFlickerLightActorBase::ToggleLight, FlickerInterval,
	                                true);
	GetWorldTimerManager().SetTimerForNextTick([this, Duration]()
	{
		FTimerHandle StopHandle;
		GetWorldTimerManager().SetTimer(StopHandle, [this]()
		{
			GetWorldTimerManager().ClearTimer(FlickerTimerHandle);
			PointLight->SetVisibility(true);
		}, Duration, false);
	});
}


void AFlickerLightActorBase::ToggleLight()
{
	PointLight->ToggleVisibility();
}
