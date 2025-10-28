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

	// UI or PostProcessing Psychological or visual disturbance events
	Hallucination UMETA(DisplayName = "Hallucination"),
	Blackout UMETA(DisplayName = "Blackout"),
	ShowMessage UMETA(DisplayName = "Show Message"),
	ShowSubtitle UMETA(DisplayName = "Show Subtitle"),
	ShowAnnouncement UMETA(DisplayName = "Show Announcement"),

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

USTRUCT(BlueprintType)
struct FSGAMEPLAY_API FShowMessageParams : public FSCustomEventParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Message")
	FText MessageText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Message")
	float Duration = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Message")
	FColor TextColor = FColor::White;

	FShowMessageParams()
	{
	}

	FShowMessageParams(const FText& InMsg, float InDuration = 3.f)
		: FSCustomEventParams(EFSEventEnum::ShowMessage),
		  MessageText(InMsg),
		  Duration(InDuration)
	{
	}
};

// ============================================================
// 💬 Subtitle Event
// ============================================================
USTRUCT(BlueprintType)
struct FSGAMEPLAY_API FShowSubtitleParams : public FSCustomEventParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Subtitle")
	FText SubtitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Subtitle")
	float Duration = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Subtitle")
	AActor* Speaker = nullptr;

	FShowSubtitleParams()
	{
	}

	FShowSubtitleParams(const FText& InSubtitle, AActor* InSpeaker = nullptr)
		: FSCustomEventParams(EFSEventEnum::ShowSubtitle),
		  SubtitleText(InSubtitle),
		  Speaker(InSpeaker)
	{
	}
};

// ============================================================
// 📢 Announcement Event
// ============================================================
USTRUCT(BlueprintType)
struct FSGAMEPLAY_API FShowAnnouncementParams : public FSCustomEventParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Announcement")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Announcement")
	FText Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Announcement")
	float DisplayTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event|Announcement")
	USoundBase* AnnouncementSound = nullptr;

	FShowAnnouncementParams()
	{
	}

	FShowAnnouncementParams(const FText& InTitle, const FText& InBody)
		: FSCustomEventParams(EFSEventEnum::ShowAnnouncement),
		  Title(InTitle),
		  Body(InBody)
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
