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

	void InitializeManager(AGameManager* gm);

    UCardBase* CreateCardViaCardID(uint32 cardID);
	bool LookUpCardDataViaID(uint32 cardID, FCardData& foundData);

	ACardActor* SpawnCardActor(UCardBase* cardBase);

	void PlayerDrawCard();
	void PlayerAddCardFromExternal(int cardID, ECardLocationType addTo);
	void PlayerDiscardCard(int discardingCardInx);

	void SetCurFocusedCard(ACardActor* cardActor);
	void SetCurSelectedCard(ACardActor* cardActor);

	FCardTransformData GetTransformData(ECardLocationType locationType);
	FCardTransformData GetInHandTransformData(int totalInHandNum, int cardIndex);
	bool GetInHandTransformPreset(int totalInHandNum, int cardIndex, FVector& pivotOffset, FRotator& rotationOffset, float& radius);
	bool GetInHandLocation_Curved(int totalInHandNum, float cardIndex, FVector& cardLocation);

	//Test Functions
	void Test_CreateDefaultCardsInDeck(int num);

private:
	void AddEscapeCardInHand();
	void RearrangeCardsInHand();
	void SetCurFocusedCard_Internal(int cardIndex);
	void SetCurSelectedCard_Internal(int cardIndex);

	FRotator GetOffsetViaIndex(FRotator rotaionOffset, int totalInHandNum, int cardIndex);

	UDataTable* m_CardDataTable;
	UDataTable* m_CardTransDataTable;
	UDataTable* m_InHandCardOffsetTable;
	UDataTable* m_CardInHandLocationCurvedTable;
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
};
