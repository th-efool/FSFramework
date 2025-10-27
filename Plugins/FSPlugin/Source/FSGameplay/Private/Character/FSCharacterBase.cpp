// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FSCharacterBase.h"


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

