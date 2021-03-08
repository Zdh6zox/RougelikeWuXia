// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleScreenWidget.generated.h"

class ACardActor;
class FCardTriggeredEvent;
class FEventListener;
/**
 * 
 */
UCLASS()
class ROUGELIKEWUXIA_API UBattleScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBattleScreenWidget(const FObjectInitializer& ObjectInitializer);
	~UBattleScreenWidget();

	UFUNCTION(BlueprintImplementableEvent, category = "Card Events")
		void OnCardFocusedEvent_BP(ACardActor* focusedCard);

	UFUNCTION(BlueprintImplementableEvent, category = "Card Events")
		void OnCardLostFocusEvent_BP(ACardActor* lostFocusCard);

	UFUNCTION(BlueprintImplementableEvent, category = "Card Events")
		void OnCardSelectedEvent_BP(ACardActor* lostFocusCard);

	UFUNCTION(BlueprintImplementableEvent, category = "Card Events")
		void OnCardUnselectedEvent_BP(ACardActor* lostFocusCard);

	UFUNCTION(BlueprintImplementableEvent, category = "Card Events")
		void OnCardAboutToTriggerEvent_BP(ACardActor* lostFocusCard);

	UFUNCTION(BlueprintImplementableEvent, category = "Card Events")
		void OnCardCancelTriggerEvent_BP(ACardActor* lostFocusCard);

	UFUNCTION(BlueprintImplementableEvent, category = "Card Events")
		void OnCardTriggeredEvent_BP(ACardActor* lostFocusCard);

public:
	void ConnectHandler();
	void DisconnectHandler();
	void AddCardEventSpy(ACardActor* spyingCard);

	void OnCardFocused(ACardActor* focusedCard);
	void OnCardLostFocus(ACardActor* lostFocusCard);
	void OnCardSelected(ACardActor* selectedCard);
	void OnCardUnselected(ACardActor* unselectedCard);
	void OnCardAboutToTrigger(ACardActor* triggeringCard);
	void OnCardCancelTrigger(ACardActor* cancelledCard);
	void OnCardTriggered(ACardActor* triggeredCard);

	void HandleCardTriggeredEvent(FCardTriggeredEvent* event);

private:
	//FEventListener* m_EventListener;
};
