// Fill out your copyright notice in the Description page of Project Settings.


#include "CardManager.h"
#include "Managers/GameManager.h"
#include "Engine/DataTable.h"
#include "Card/CardData.h"
#include "Card/CardBase.h"
#include "Card/CardTransformDataPreset.h"
#include "Card/CardTransTableMap.h"
#include "Card/CardActor.h"
#include "RougelikeWuXia.h"

void FCardManager::InitializeManager(AGameManager* gm)
{
	m_GMCache = gm;

	FString tableMapPath = "DataTable'/Game/DataTable/CardTransTableMap.CardTransTableMap'";
	m_CardTransDataTableMap = LoadObject<UDataTable>(NULL, *tableMapPath);
	check(m_CardTransDataTableMap != NULL);

	m_CardsInDeck.Empty();
	m_CardActors.Empty();
	m_CardsInHand.Empty();
	m_AllPlayerCards.Empty();
	m_DiscardedCards.Empty();
	m_DestroyedCards.Empty();
}

UCardBase* FCardManager::CreateCardViaCardID(uint32 cardID)
{
    UDataTable* cardTable = m_GMCache->CardDataTable;
    if (cardTable == nullptr)
    {
        UE_LOG(LogMain, Error, TEXT("Cannot find card data table!"));
        return nullptr;
    }
    
    TArray<FStringFormatArg> args;
    args.Add(FStringFormatArg(cardID));
    FName rowNameFromID = FName(*FString::Format(TEXT("{0}"), args));
    FCardData* foundData = cardTable->FindRow<FCardData>(rowNameFromID, "");
    if (foundData == nullptr)
    {
        UE_LOG(LogMain, Error, TEXT("Cannot find card data row %d"), cardID);
        return nullptr;
    }

    UCardBase* newCard = NewObject<UCardBase>();
    newCard->InitializeFromCardData(*foundData);

    m_AllPlayerCards.Add(newCard);

    return newCard;
}

FCardTransformData FCardManager::GetTransformData(ECardLocationType locationType, int totalInHandNum, int cardIndex)
{
	UDataTable* tableToSearch = nullptr;
	TArray<FCardTransTableMap*> allTables;
	m_CardTransDataTableMap->GetAllRows<FCardTransTableMap>(FString(""), allTables);
	switch (locationType)
	{
	case ECardLocationType::Deck:
	case ECardLocationType::Discarded:
	case ECardLocationType::External:
	{
		for (int i = 0; i < allTables.Num(); ++i)
		{
			if (allTables[i]->CardLocationType == locationType)
			{
				tableToSearch = allTables[i]->CardTransTable;
				break;
			}
		}
	}
		break;
	case ECardLocationType::InHand:
	{
		for (int i = 0; i < allTables.Num(); ++i)
		{
			if (allTables[i]->CardLocationType == ECardLocationType::InHand && allTables[i]->TotalCardNumOnHand == totalInHandNum)
			{
				tableToSearch = allTables[i]->CardTransTable;
				break;
			}
		}
	}
		break;
	default:
		break;
	}

	check(tableToSearch);

	TArray<FCardTransformDataPreset*> allTransPreset;
	tableToSearch->GetAllRows<FCardTransformDataPreset>(FString(""), allTransPreset);
	FCardTransformData newTransformData;
	newTransformData.CardLocationType = locationType;
	newTransformData.CardInHandIndex = cardIndex;
	bool foundTransformInTable = false;

	switch (locationType)
	{
	case ECardLocationType::Deck:
	case ECardLocationType::Discarded:
	case ECardLocationType::External:
	{
		for (int i = 0; i < allTransPreset.Num(); ++i)
		{
			if (allTransPreset[i]->CardLocationType == locationType)
			{
				newTransformData.CardTransform = allTransPreset[i]->CardTransform;
				foundTransformInTable = true;
				break;
			}
		}
	}
		break;
	case ECardLocationType::InHand:
	{
		for (int i = 0; i < allTransPreset.Num(); ++i)
		{
			if (allTransPreset[i]->CardInHandIndex == cardIndex)
			{
				newTransformData.CardTransform = allTransPreset[i]->CardTransform;
				foundTransformInTable = true;
				break;
			}
		}
	}
	    break;
	default:
		break;
	}

	check(foundTransformInTable);

#ifdef WITH_EDITOR
	UE_LOG(LogMain, Log, TEXT("found Transform %s"), *newTransformData.CardTransform.ToString());
#endif

	return newTransformData;
}

void FCardManager::PlayerDrawCard()
{
	if (m_CardsInDeck.Num() == 0)
	{
		AddEscapeCardInHand();
		return;
	}
	int drawingCardDeckIndex = m_GMCache->GetRandomStream().RandRange(0, m_CardsInDeck.Num() - 1);

	UCardBase* drawingCard = m_CardsInDeck[drawingCardDeckIndex];
	m_CardsInHand.Insert(drawingCard, 0);
	m_CardsInDeck.RemoveAt(drawingCardDeckIndex);
	
	SpawnCardActor(drawingCard, GetTransformData(ECardLocationType::Deck, m_CardsInHand.Num(), 0));

	RearrangeCardsInHand();
}

void FCardManager::PlayerAddCardFromExternal(int cardID, ECardLocationType addTo)
{

}

void FCardManager::PlayerDiscardCard(UCardBase* discardingCard)
{

}

void FCardManager::SpawnCardActor(UCardBase* cardBase, FCardTransformData cardTrans)
{
	ACardActor* spawnedActor = m_GMCache->GetWorld()->SpawnActor<ACardActor>(ACardActor::StaticClass(), cardTrans.CardTransform);
	spawnedActor->CardTransformData = cardTrans;
	spawnedActor->Card = cardBase;
	m_CardActors.Add(spawnedActor);
}

void FCardManager::AddEscapeCardInHand()
{
	//add unique escape card in hand,
	//if escape card already in hand, add debuff card
}

void FCardManager::RearrangeCardsInHand()
{
	for (int i = 0; i < m_CardsInHand.Num(); ++i)
	{
		auto* actorPtr = m_CardActors.FindByPredicate([&](ACardActor* actor)
		{
			return actor->Card == m_CardsInHand[i];
		});

		if (actorPtr != nullptr)
		{
			ACardActor* foundActor = *actorPtr;
			FCardTransformData newTrans = GetTransformData(ECardLocationType::InHand, m_CardsInHand.Num(), i);
			foundActor->CardTransformTo(newTrans);
		}
	}
}

//Test Functions
void FCardManager::Test_CreateDefaultCardsInDeck(int num)
{
	for (int i = 0; i < num; ++i)
	{
		UCardBase* newCard = CreateCardViaCardID(0);
		m_CardsInDeck.Add(newCard);
	}
}