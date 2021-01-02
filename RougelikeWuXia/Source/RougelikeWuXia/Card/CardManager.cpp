// Fill out your copyright notice in the Description page of Project Settings.


#include "CardManager.h"
#include "Managers/GameManager.h"
#include "Engine/DataTable.h"
#include "Card/CardData.h"
#include "Card/CardBase.h"
#include "Card/CardTransformDataPreset.h"
#include "Card/CardTransTableMap.h"
#include "RougelikeWuXia.h"

void FCardManager::InitializeManager(AGameManager* gm)
{
	m_GMCache = gm;

	FString tableMapPath = "DataTable'/Game/DataTable/CardTransTableMap.CardTransTableMap'";
	m_CardTransDataTableMap = LoadObject<UDataTable>(NULL, *tableMapPath);
	check(m_CardTransDataTableMap != NULL);
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