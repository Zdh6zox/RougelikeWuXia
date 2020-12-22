// Fill out your copyright notice in the Description page of Project Settings.


#include "CardManager.h"
#include "Managers/GameManager.h"
#include "Engine/DataTable.h"
#include "Card/CardData.h"
#include "Card/CardBase.h"
#include "RougelikeWuXia.h"

void FCardManager::InitializeManager(AGameManager* gm)
{
	m_GMCache = gm;
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

    m_ExistingCards.Add(newCard);

    return newCard;
}