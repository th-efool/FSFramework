// Fill out your copyright notice in the Description page of Project Settings.


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

	/** Called when widget is constructed */
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

	/** Refreshes button states and username display */
	void UpdateUIState();

	void OnEOSLoginStatusChanged(bool bLoggedIn);

};
