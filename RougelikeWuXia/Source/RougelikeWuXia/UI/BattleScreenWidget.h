// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleScreenWidget.generated.h"

class ACardActor;
/**
 * 
 */
UCLASS()
class ROUGELIKEWUXIA_API UBattleScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, category = "Card Events")
		void OnCardFocusedEvent_BP(ACardActor* focusedCard);

	UFUNCTION(BlueprintImplementableEvent, category = "Card Events")
		void OnCardLostFocusEvent_BP(ACardActor* lostFocusCard);

public:
	void AddCardEventSpy(ACardActor* spyingCard);

	void OnCardFocused(ACardActor* focusedCard);
	void OnCardLostFocus(ACardActor* lostFocusCard);


};
