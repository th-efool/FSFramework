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
