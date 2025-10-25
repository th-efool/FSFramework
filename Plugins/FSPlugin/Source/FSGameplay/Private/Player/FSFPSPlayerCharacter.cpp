// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FSFPSPlayerCharacter.h"


// Sets default values
AFSFPSPlayerCharacter::AFSFPSPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Third Person Settings --> First Person Settings
	bUseControllerRotationYaw = true;
	CameraBoom->bInheritPitch = true;
	CameraBoom->bInheritYaw = true;

	CameraBoom->TargetArmLength=0.0f;
	CameraBoom->SetRelativeLocation(FVector(39,7.f,48.0f));
	
}

// Called when the game starts or when spawned
void AFSFPSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFSFPSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Tilt = FMath::Lerp(Tilt, 0, TiltRecoverySpeed * DeltaTime);
	CameraBoom->SetWorldRotation(GetController()->GetControlRotation());
	CameraBoom->AddRelativeRotation((FRotator(0,0,Tilt)));
	
}

// Called to bind functionality to input
void AFSFPSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}




void AFSFPSPlayerCharacter::DoLook(float Yaw, float Pitch)
{
	Super::DoLook(Yaw, Pitch);
	Tilt += Yaw;
	Tilt=FMath::Clamp(Tilt, -MaxTilt, MaxTilt);
}

