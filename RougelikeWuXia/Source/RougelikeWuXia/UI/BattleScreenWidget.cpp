// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleScreenWidget.h"
#include "Card/CardActor.h"

void UBattleScreenWidget::AddCardEventSpy(ACardActor* spyingCard)
{
	spyingCard->CardFocusedEvent_OneP.AddUObject(this, &UBattleScreenWidget::OnCardFocused);
	spyingCard->CardLostFocusEvent_OneP.AddUObject(this, &UBattleScreenWidget::OnCardLostFocus);
}

void UBattleScreenWidget::OnCardFocused(ACardActor* focusedCard)
{
	OnCardFocusedEvent_BP(focusedCard);
}

void UBattleScreenWidget::OnCardLostFocus(ACardActor* lostFocusCard)
{
	OnCardLostFocusEvent_BP(lostFocusCard);
}