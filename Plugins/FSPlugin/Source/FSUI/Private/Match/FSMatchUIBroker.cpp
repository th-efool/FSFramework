// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/FSMatchUIBroker.h"


void UFSMatchUIBroker::RelaySanity(float newPercentage)
{
	if (!IsValid(this)) return;
	OnUISanityChanged.Broadcast(newPercentage);
}

void UFSMatchUIBroker::RelayHealth(float newPercentage)
{
	if (!IsValid(this)) return;
	OnUIHealthChanged.Broadcast(newPercentage);
}

void UFSMatchUIBroker::RelayAnnouncement(const FText& text, float lifetime)
{
	if (!IsValid(this)) return;
	OnUIAnnouncement.Broadcast(text, lifetime);
}

void UFSMatchUIBroker::RelaySubtitle(const FText& text, float lifetime)
{
	if (!IsValid(this)) return;
	OnUISubtitle.Broadcast(text, lifetime);
}

void UFSMatchUIBroker::RelayDiaryShow(const FText& date, const FText& body)
{
	if (!IsValid(this)) return;
	OnUIDiaryShow.Broadcast(date, body);
}

void UFSMatchUIBroker::RelayDiaryHide()
{
	if (!IsValid(this)) return;
	OnUIDiaryHide.Broadcast();
}

void UFSMatchUIBroker::RelayDropButtonPressed(EInventoryItem Item, int Amount)
{
	OnUIItemDropped.Broadcast(Item,Amount);
}

void UFSMatchUIBroker::RelayConsumeButtonPressed(EInventoryItem Item)
{
	OnUIItemConsumed.Broadcast(Item);
}

