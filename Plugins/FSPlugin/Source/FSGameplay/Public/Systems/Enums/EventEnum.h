#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "Systems/Interface/FSFlicker.h"
#include "EventEnum.generated.h"

UENUM(BlueprintType)
enum class EFSEventEnum : uint8
{
	None UMETA(DisplayName = "None"),
	// Early-stage atmospheric or ambient effects
	LightFlicker UMETA(DisplayName = "Light Flicker"),
	SoundPlay UMETA(DisplayName = "Play Sound"),
	Hallucination UMETA(DisplayName = "Hallucination"),

	// Intense horror interactions
	JumpScare UMETA(DisplayName = "Jump Scare"),
	Teleport UMETA(DisplayName = "Teleport"),

	// Gameplay control effects
	DisablePlayerLights UMETA(DisplayName = "Disable Player Lights"),
};


USTRUCT(BlueprintType)
struct FSGAMEPLAY_API FSCustomEventParams
{
	GENERATED_BODY()

	UPROPERTY()
	EFSEventEnum EventName = EFSEventEnum::None; // or FGameplayTag if you use them

	FSCustomEventParams()
	{
	}

	explicit FSCustomEventParams(EFSEventEnum InTag)
		: EventName(InTag)
	{
	}
};


USTRUCT(BlueprintType)
struct FSGAMEPLAY_API FTeleportParams : public FSCustomEventParams
{
	GENERATED_BODY()

	UPROPERTY()
	FVector TargetLocation = FVector(0, 0, 0);

	FTeleportParams()
	{
	}

	FTeleportParams(const FVector& InTarget)
		: FSCustomEventParams(EFSEventEnum::Teleport)
		  , TargetLocation(InTarget)
	{
	}
};

// ============================================================
// 🔊 Sound Play Event
// ============================================================
USTRUCT(BlueprintType)
struct FSGAMEPLAY_API FSoundPlayParams : public FSCustomEventParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Sound")
	USoundBase* Sound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Sound")
	FVector Location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Sound")
	float VolumeMultiplier = 1.0f;

	FSoundPlayParams()
	{
	}

	FSoundPlayParams(USoundBase* InSound, FVector InLocation = FVector::ZeroVector)
		: FSCustomEventParams(EFSEventEnum::SoundPlay),
		  Sound(InSound),
		  Location(InLocation)
	{
	}
};

// ============================================================
// 💡 Light Flicker Event
// ============================================================
USTRUCT(BlueprintType)
struct FSGAMEPLAY_API FLightFlickerParams : public FSCustomEventParams
{
	GENERATED_BODY()

	// Array of actors that implement IFSFlicker
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Light")
	TArray<TScriptInterface<IFSFlicker>> FlickerActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Light")
	float FlickerDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Light")
	float IntensityScale = 1.0f;

	FLightFlickerParams()
	{
	}

	FLightFlickerParams(const TArray<TScriptInterface<class IFSFlicker>>& InActors)
		: FSCustomEventParams(EFSEventEnum::LightFlicker),
		  FlickerActors(InActors)
	{
	}
};
