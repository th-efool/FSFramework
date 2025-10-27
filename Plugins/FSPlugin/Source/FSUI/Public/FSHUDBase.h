// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSUserWidgetBase.h"
#include "GameFramework/HUD.h"
#include "FSHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class FSUI_API AFSHUDBase : public AHUD
{
	GENERATED_BODY()

	public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	TArray<TSubclassOf<UFSUserWidgetBase>> WidgetsClassArray;

	UPROPERTY()
	TArray<UFSUserWidgetBase*> WidgetObjectArray;
	
	protected:
	void InitializedWidgets();
};
