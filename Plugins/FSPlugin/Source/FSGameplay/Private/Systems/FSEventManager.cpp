// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/FSEventManager.h"

#include "K2Node_GetSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Systems/FSGameplayBroker.h"


void UFSEventManager::TriggerEvent(EFSEventEnum EventType, AActor* Instigator,
                                   const FSCustomEventParams& CustomEventParams)
{

	
	OnEventTriggered.Broadcast(EventType, Instigator);

	// Handle in C++ if needed (game-specific routing)
	switch (EventType)
	{
	case EFSEventEnum::LightFlicker:
		{
			const FLightFlickerParams& Params = static_cast<const FLightFlickerParams&>(CustomEventParams);


			for (const TScriptInterface<IFSFlicker>& Target : Params.FlickerActors)
			{
				UObject* Obj = Target.GetObject();
				if (IsValid(Obj) && Obj->GetClass()->ImplementsInterface(UFSFlicker::StaticClass()))
				{
					IFSFlicker::Execute_SetIntensityFlicker(Obj, Params.IntensityScale);
					IFSFlicker::Execute_Flicker(Obj, Params.FlickerDuration);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Invalid or non-interface actor in FlickerActors array"));
				}
			}
			break;
		}
	case EFSEventEnum::SoundPlay:
		{
			const FSoundPlayParams& Params = static_cast<const FSoundPlayParams&>(CustomEventParams);
			if (Params.Sound)
			{
				UGameplayStatics::PlaySoundAtLocation(Instigator, Params.Sound, Params.Location,
				                                      Params.VolumeMultiplier);
			}
			break;
		}
	case EFSEventEnum::Teleport:
		{
			const FTeleportParams& Params = static_cast<const FTeleportParams&>(CustomEventParams);
			if (Instigator)
			{
				Instigator->SetActorLocation(Params.TargetLocation);
			}
			break;
		}
	case EFSEventEnum::JumpScare:
		{

			break;
		}
	case EFSEventEnum::Hallucination:
		{

			break;
		}

		case EFSEventEnum::DisablePlayerLights:
		{
			
		}
	default:
		break;
	}
}

void UFSEventManager::PlaySound(AActor* Instigator, USoundBase* Sound, FVector Location,
                                         float VolumeMultiplier)
{
	FSoundPlayParams Params(Sound, Location);
	Params.VolumeMultiplier = VolumeMultiplier;
	TriggerEvent(EFSEventEnum::SoundPlay, Instigator, Params);
}

void UFSEventManager::TriggerLightFlicker(AActor* Instigator,
                                                   const TArray<TScriptInterface<IFSFlicker>>& FlickerActors,
                                                   float Duration, float IntensityScale)
{
	FLightFlickerParams Params(FlickerActors);
	Params.FlickerDuration = Duration;
	Params.IntensityScale = IntensityScale;
	TriggerEvent(EFSEventEnum::LightFlicker, Instigator, Params);
}

void UFSEventManager::TeleportActor(AActor* Instigator, const FVector& TargetLocation)
{
	FTeleportParams Params(TargetLocation);
	TriggerEvent(EFSEventEnum::Teleport, Instigator, Params);
}
