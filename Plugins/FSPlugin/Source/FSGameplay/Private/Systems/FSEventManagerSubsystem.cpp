// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/FSEventManagerSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Systems/Interface/FSFlicker.h"

void UFSEventManagerSubsystem::TriggerEvent(EFSEventEnum EventType, AActor* Instigator, const FSCustomEventParams& CustomEventParams)
{
	OnEventTriggered.Broadcast(EventType, Instigator);

	// Handle in C++ if needed (game-specific routing)
	switch (EventType)
	{
	case EFSEventEnum::LightFlicker:
	{
		const FLightFlickerParams& Params = static_cast<const FLightFlickerParams&>(CustomEventParams);
		for (auto& Target : Params.FlickerActors)
		{
			if (Target){
                IFSFlicker::Execute_Flicker(Target.GetObject(), Params.FlickerDuration);
			}
		}
		break;
	}
	case EFSEventEnum::SoundPlay:
	{
		const FSoundPlayParams& Params = static_cast<const FSoundPlayParams&>(CustomEventParams);
		if (Params.Sound)
			UGameplayStatics::PlaySoundAtLocation(Instigator, Params.Sound, Params.Location, Params.VolumeMultiplier);
		break;
	}
	case EFSEventEnum::Teleport:
	{
		const FTeleportParams& Params = static_cast<const FTeleportParams&>(CustomEventParams);
		if (Instigator)
			Instigator->SetActorLocation(Params.TargetLocation);
		break;
	}
	default:
		break;
	}
}

void UFSEventManagerSubsystem::ShowMessage(AActor* Instigator, const FText& Message, float Duration, FColor TextColor)
{
	FShowMessageParams Params(Message, Duration);
	Params.TextColor = TextColor;
	TriggerEvent(EFSEventEnum::ShowMessage, Instigator, Params);
}

void UFSEventManagerSubsystem::ShowSubtitle(AActor* Instigator, const FText& Subtitle, AActor* Speaker, float Duration)
{
	FShowSubtitleParams Params(Subtitle, Speaker);
	Params.Duration = Duration;
	TriggerEvent(EFSEventEnum::ShowSubtitle, Instigator, Params);
}

void UFSEventManagerSubsystem::ShowAnnouncement(AActor* Instigator, const FText& Title, const FText& Body, float DisplayTime, USoundBase* AnnouncementSound)
{
	FShowAnnouncementParams Params(Title, Body);
	Params.DisplayTime = DisplayTime;
	Params.AnnouncementSound = AnnouncementSound;
	TriggerEvent(EFSEventEnum::ShowAnnouncement, Instigator, Params);
}

void UFSEventManagerSubsystem::PlaySound(AActor* Instigator, USoundBase* Sound, FVector Location, float VolumeMultiplier)
{
	FSoundPlayParams Params(Sound, Location);
	Params.VolumeMultiplier = VolumeMultiplier;
	TriggerEvent(EFSEventEnum::SoundPlay, Instigator, Params);
}

void UFSEventManagerSubsystem::TriggerLightFlicker(AActor* Instigator, const TArray<TScriptInterface<IFSFlicker>>& FlickerActors, float Duration, float IntensityScale)
{
	FLightFlickerParams Params(FlickerActors);
	Params.FlickerDuration = Duration;
	Params.IntensityScale = IntensityScale;
	TriggerEvent(EFSEventEnum::LightFlicker, Instigator, Params);
}

void UFSEventManagerSubsystem::TeleportActor(AActor* Instigator, const FVector& TargetLocation)
{
	FTeleportParams Params(TargetLocation);
	TriggerEvent(EFSEventEnum::Teleport, Instigator, Params);
}


