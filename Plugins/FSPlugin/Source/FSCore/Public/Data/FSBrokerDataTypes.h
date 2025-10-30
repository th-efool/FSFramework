#pragma once
#include "CoreMinimal.h"              // ✅ Required before USTRUCT/UCLASS
#include "GameFramework/PlayerState.h" // If you use APlayerState pointer
#include "FSBrokerDataTypes.generated.h" // ✅ Always include generated header LAST


USTRUCT(BlueprintType)
struct FPlayerJoinInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<APlayerState> PlayerState = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bIsLocalPlayer = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerJoinedSignature, const FPlayerJoinInfo&, Info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerLeftSignature, APlayerState*, PlayerState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSanityChangedSignature, float, SanityPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChangedSignature, float, HealthPercent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAnnouncementSignature, const FText&, Message, float, Time);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSubtitleSignature, const FText&, Message, float, Time);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDiaryShowSignature, const FText&, Date, const FText&, Body);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDiaryHideSignature);
