// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardTransformData.h"

class UCardBase;
class AGameManager;
class UDataTable;
class ACardActor;
struct FCardData;

/**
 * 
 */
class ROUGELIKEWUXIA_API FCardManager
{
public:
	enum CardManagerMode
	{
		Browse,
		MovingCard,
		Triggering
	};

	void InitializeManager(AGameManager* gm);
	void UpdateCards();

    UCardBase* CreateCardViaCardID(uint32 cardID);
	void SpawnCardActor(UCardBase* cardBase, FCardTransformData cardTrans);

	void PlayerDrawCard();
	void PlayerAddCardFromExternal(int cardID, ECardLocationType addTo);
	void PlayerDiscardCard(UCardBase* discardingCard);
	void SetCurFocusedCard(int cardIndex);
	void SetCurFocusedCard(ACardActor* cardActor);
	void SetCurSelectedCard(int cardIndex);
	void SetCurSelectedCard(ACardActor* cardActor);

	FCardTransformData GetTransformData(ECardLocationType locationType, int totalInHandNum, int cardIndex);

	UCardBase* GetCurFocusedCardInHand();

	//Test Functions
	void Test_CreateDefaultCardsInDeck(int num);

private:
	void AddEscapeCardInHand();
	void RearrangeCardsInHand();

	FRotator GetOffsetViaIndex(FRotator rotaionOffset, int totalInHandNum, int cardIndex);

	UDataTable* m_CardTransDataTable;
	UDataTable* m_InHandCardOffsetTable;
	AGameManager* m_GMCache;
    TArray<UCardBase*> m_AllPlayerCards;

	TArray<UCardBase*> m_CardsInDeck;
	TArray<UCardBase*> m_DiscardedCards;
	TArray<UCardBase*> m_CardsInHand;
	TArray<UCardBase*> m_DestroyedCards;

	TArray<ACardActor*> m_CardActors;
	ACardActor* m_CurSelectedCard = nullptr;
	int m_CurFocusedInHandCardInx = -1;
	int m_CurSelectedInHandCardInx = -1;
	UClass* m_CardActorClass;
	CardManagerMode m_Mode;
};
