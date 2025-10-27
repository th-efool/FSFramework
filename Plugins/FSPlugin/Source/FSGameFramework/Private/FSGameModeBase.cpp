// Fill out your copyright notice in the Description page of Project Settings.


#include "FSGameModeBase.h"

#include "FSGameStateBase.h"
#include "FSPlayerControllerBase.h"
#include "FSPlayerStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AFSGameModeBase::AFSGameModeBase()
{
	PlayerControllerClass = AFSPlayerControllerBase::StaticClass();
	GameStateClass        = AFSGameStateBase::StaticClass();
	PlayerStateClass      = AFSPlayerStateBase::StaticClass();
}

AActor* AFSGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

	if (PlayerStarts.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerStart found in the level!"));
		return nullptr;
	}

	// Find used PlayerStart locations
	TArray<FVector> UsedLocations;
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AController* ExistingController = It->Get();
		if (ExistingController && ExistingController->GetPawn())
		{
			UsedLocations.Add(ExistingController->GetPawn()->GetActorLocation());
		}
	}

	// Look for a PlayerStart not too close to used locations
	const float MinDistance = 200.0f;
	for (AActor* Start : PlayerStarts)
	{
		bool bTooClose = false;
		for (const FVector& Used : UsedLocations)
		{
			if (FVector::Dist(Used, Start->GetActorLocation()) < MinDistance)
			{
				bTooClose = true;
				break;
			}
		}

		if (!bTooClose)
		{
			UE_LOG(LogTemp, Log, TEXT("Selected PlayerStart: %s"), *Start->GetName());
			return Start;
		}
	}

	// All starts are close — pick the first and apply offset
	AActor* FallbackStart = PlayerStarts[0];
	FVector OffsetLoc = FallbackStart->GetActorLocation() + FVector(300.f * UsedLocations.Num(), 0, 0);
	FRotator Rot = FallbackStart->GetActorRotation();

	// Spawn a temporary offset spawn point
	APlayerStart* TempStart = GetWorld()->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), OffsetLoc, Rot);
	return TempStart;

}
