// Fill out your copyright notice in the Description page of Project Settings.


#include "FSHUDBase.h"

#include "GameFramework/GameSession.h"

void AFSHUDBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFSHUDBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		InitializedWidgets();
	});
}

void AFSHUDBase::DrawHUD()
{
	Super::DrawHUD();
}

void AFSHUDBase::InitializedWidgets()
{
	for (auto widgetclass : WidgetsClassArray)
	{
		if (widgetclass)
		{
			if (UFSUserWidgetBase* widget = CreateWidget<UFSUserWidgetBase>(
				GetWorld()->GetFirstPlayerController(), widgetclass))
			{
				WidgetObjectArray.Add(widget);
				widget->AddToViewport();
			}
		}
	}
}
