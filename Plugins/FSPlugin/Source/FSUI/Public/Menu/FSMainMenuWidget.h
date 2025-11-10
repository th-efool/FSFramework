#pragma once

#include "CoreMinimal.h"
#include "Base/FSHUDWidgetBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FSMainMenuWidget.generated.h"

UCLASS()
class FSUI_API UFSMainMenuWidget : public UFSHUDWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	/** --- UI Bindings --- */
	UPROPERTY(meta = (BindWidget))
	UButton* PlaySoloButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MultiplayerButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* LoginWithEOSButton;

	UPROPERTY(meta = (BindWidget))
	UButton* LoginDevButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* UsernameText;

	/** --- Internal State --- */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Login")
	bool bIsLoggedIn = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Login")
	FString CachedPlayerName = TEXT("Guest");

	/** --- Button Callbacks --- */
	UFUNCTION()
	void OnPlaySoloClicked();

	UFUNCTION()
	void OnMultiplayerClicked();

	UFUNCTION()
	void OnSettingsClicked();

	UFUNCTION()
	void OnLoginWithEOSClicked();

	UFUNCTION()
	void OnLoginDevClicked();

	/** --- Broker Delegates --- */
	UFUNCTION()
	void HandleLoginResult(bool bSuccess, const FString& Error);

	UFUNCTION()
	void HandleDevAuthResult(bool bSuccess, const FString& Error);

	/** Update the UI (buttons + name) */
	void UpdateUIState();
};
