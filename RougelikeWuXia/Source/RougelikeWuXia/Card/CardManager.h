// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardTransformData.h"

class UCardBase;
class AGameManager;
class UDataTable;
class ACardActor;
class ACardMovingPlane;
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
	void SpawnCardActor(UCardBase* cardBase);

	void PlayerDrawCard();
	void PlayerAddCardFromExternal(int cardID, ECardLocationType addTo);
	void PlayerDiscardCard(int discardingCardInx);

	void SetCurFocusedCard(ACardActor* cardActor);
	void SetCurSelectedCard(ACardActor* cardActor);

	void SetCardManagerMode(CardManagerMode mode);

	FCardTransformData GetTransformData(ECardLocationType locationType);
	FCardTransformData GetInHandTransformData(int totalInHandNum, int cardIndex);

	//Test Functions
	void Test_CreateDefaultCardsInDeck(int num);

private:
	void AddEscapeCardInHand();
	void RearrangeCardsInHand();
	void SetCurFocusedCard_Internal(int cardIndex);
	void SetCurSelectedCard_Internal(int cardIndex);

	FRotator GetOffsetViaIndex(FRotator rotaionOffset, int totalInHandNum, int cardIndex);

	UDataTable* m_CardTransDataTable;
	UDataTable* m_InHandCardOffsetTable;
	AGameManager* m_GMCache;
    TArray<UCardBase*> m_AllPlayerCards;

	TArray<ACardActor*> m_CardActors;
	TArray<UCardBase*> m_CardsInDeck;
	TArray<UCardBase*> m_DiscardedCards;
	TArray<UCardBase*> m_DestroyedCards;


	ACardActor* m_CurSelectedCard = nullptr;
	int m_CurFocusedInHandCardInx = -1;
	int m_CurSelectedInHandCardInx = -1;
	UClass* m_CardActorClass;
	CardManagerMode m_Mode;

	ACardMovingPlane* m_CardMovingPlane;
};
