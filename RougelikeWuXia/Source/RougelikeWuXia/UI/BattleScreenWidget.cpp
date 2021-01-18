// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleScreenWidget.h"
#include "Card/CardActor.h"

void UBattleScreenWidget::AddCardEventSpy(ACardActor* spyingCard)
{
	spyingCard->CardFocusedEvent_OneP.AddUObject(this, &UBattleScreenWidget::OnCardFocused);
	spyingCard->CardLostFocusEvent_OneP.AddUObject(this, &UBattleScreenWidget::OnCardLostFocus);
	spyingCard->CardSelectedEvent_OneP.AddUObject(this, &UBattleScreenWidget::OnCardSelected);
	spyingCard->CardUnselectedEvent_OneP.AddUObject(this, &UBattleScreenWidget::OnCardUnselected);
	spyingCard->CardAboutToTriggerEvent_OneP.AddUObject(this, &UBattleScreenWidget::OnCardAboutToTrigger);
	spyingCard->CardCancelTriggerEvent_OneP.AddUObject(this, &UBattleScreenWidget::OnCardCancelTrigger);
	spyingCard->CardTriggeredEvent_OneP.AddUObject(this, &UBattleScreenWidget::OnCardTriggered);
}

void UBattleScreenWidget::OnCardFocused(ACardActor* focusedCard)
{
	OnCardFocusedEvent_BP(focusedCard);
}

void UBattleScreenWidget::OnCardLostFocus(ACardActor* lostFocusCard)
{
	OnCardLostFocusEvent_BP(lostFocusCard);
}

void UBattleScreenWidget::OnCardSelected(ACardActor* selectedCard)
{
	OnCardSelectedEvent_BP(selectedCard);
}

void UBattleScreenWidget::OnCardUnselected(ACardActor* unselectedCard)
{
	OnCardUnselectedEvent_BP(unselectedCard);
}

void UBattleScreenWidget::OnCardAboutToTrigger(ACardActor* triggeringCard)
{
	OnCardAboutToTriggerEvent_BP(triggeringCard);
}

void UBattleScreenWidget::OnCardCancelTrigger(ACardActor* cancelledCard)
{
	OnCardCancelTriggerEvent_BP(cancelledCard);
}

void UBattleScreenWidget::OnCardTriggered(ACardActor* triggeredCard)
{
	OnCardTriggeredEvent_BP(triggeredCard);
}