// Fill out your copyright notice in the Description page of Project Settings.


#include "CardManager.h"
#include "Managers/GameManager.h"
#include "EngineUtils.h"
#include "Engine/DataTable.h"
#include "Card/CardData.h"
#include "Card/CardBase.h"
#include "Card/CardTransformDataPreset.h"
#include "Card/CardActor.h"
#include "UI/BattleScreenWidget.h"
#include "ScreenOnlyPlayerController.h"
#include "RougelikeWuXia.h"


#pragma optimize( "", off )

void FCardManager::InitializeManager(AGameManager* gm)
{
	m_GMCache = gm;

	FString cardTransTablePath = "DataTable'/Game/DataTable/CardTransformPreset_Global.CardTransformPreset_Global'";
	m_CardTransDataTable = LoadObject<UDataTable>(NULL, *cardTransTablePath);
	check(m_CardTransDataTable != NULL);

	FString inHandOffsetTablePath = "DataTable'/Game/DataTable/CardInHandOffet.CardInHandOffet'";
	m_InHandCardOffsetTable = LoadObject<UDataTable>(NULL, *inHandOffsetTablePath);
	check(m_InHandCardOffsetTable != NULL);

	m_CardDataTable = m_GMCache->CardDataTable;

	FString cardActorPath = "Blueprint'/Game/Card/CardActor_BP.CardActor_BP_C'";
	m_CardActorClass = LoadClass<ACardActor>(NULL, *cardActorPath);
	check(m_CardActorClass != NULL);

	m_CardsInDeck.Empty();
	m_CardActors.Empty();
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

bool FCardManager::LookUpCardDataViaID(uint32 cardID, FCardData& foundData)
{
	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(cardID));
	FName rowNameFromID = FName(*FString::Format(TEXT("{0}"), args));
	FCardData* cardData = m_CardDataTable->FindRow<FCardData>(rowNameFromID, "");
	if (cardData == nullptr)
	{
		UE_LOG(LogMain, Error, TEXT("Cannot find card data row %d"), cardID);
		return false;
	}

	foundData = *cardData;
	return true;
}

FCardTransformData FCardManager::GetTransformData(ECardLocationType locationType)
{
	UDataTable* tableToSearch = nullptr;
	FCardTransformData foundNewTrans;
	TArray<FCardTransformDataPreset*> allTrans;
	m_CardTransDataTable->GetAllRows<FCardTransformDataPreset>(FString(""), allTrans);
	bool foundTrans = false;
	switch (locationType)
	{
	case ECardLocationType::Deck:
	case ECardLocationType::Discarded:
	case ECardLocationType::External:
	{
		for (int i = 0; i < allTrans.Num(); ++i)
		{
			if (allTrans[i]->CardLocationType == locationType)
			{
				foundNewTrans.CardTransform = allTrans[i]->CardTransform;
				foundNewTrans.CardLocationType = locationType;
				foundNewTrans.CardInHandIndex = 0;
				foundTrans = true;
				break;
			}
		}
	}
		break;
	default:
		break;
	}

	check(foundTrans);

	return foundNewTrans;
}

FCardTransformData FCardManager::GetInHandTransformData(int totalInHandNum, int cardIndex)
{
	FCardTransformData foundNewTrans;

	FTransform trans;
	TArray<FCardTransformDataPreset*> allTrans;
	m_CardTransDataTable->GetAllRows<FCardTransformDataPreset>(FString(""), allTrans);
	for (int i = 0; i < allTrans.Num(); i++)
	{
		if (allTrans[i]->CardLocationType == ECardLocationType::InHand)
		{
			trans = allTrans[i]->CardTransform;
			break;
		}
	}

	bool foundTrans = false;
	TArray<FInHandCardTransOffsetPreset*> allOffset;
	m_InHandCardOffsetTable->GetAllRows<FInHandCardTransOffsetPreset>(FString(""), allOffset);
	FRotator offset;
	for (int j = 0; j < allOffset.Num(); ++j)
	{
		if (allOffset[j]->TotalNumberInHand == totalInHandNum)
		{
			offset = allOffset[j]->CardRotaionOffset;

			//Change card transform according to card index;
			FRotator cameraRotate = FRotator(-m_GMCache->GetCameraRotation().Pitch, 0.0f, 0.0f);
			FVector camVec = cameraRotate.RotateVector(m_GMCache->GetCameraUpVector());
			FVector pivot = trans.GetLocation() + camVec * allOffset[j]->CardPivotOffset.Z;
			FTransform pivotTrans = FTransform(cameraRotate, pivot);
			FRotator finalRotOffset = GetOffsetViaIndex(offset, totalInHandNum, cardIndex);
			FVector finalVec = finalRotOffset.RotateVector(m_GMCache->GetCameraUpVector());
			FVector finalLoc = allOffset[j]->Radius * finalVec;
			//add little bias to avoid overlap
			finalLoc = finalLoc + m_GMCache->GetCameraForwardVector() * 0.01f * cardIndex;
			FTransform relativeTrans = FTransform(finalRotOffset, finalLoc);


			foundNewTrans.CardTransform = relativeTrans * pivotTrans;
			foundNewTrans.CardInHandIndex = cardIndex;
			foundTrans = true;
			break;
		}
	}

	check(foundTrans);
	return foundNewTrans;
}

FRotator FCardManager::GetOffsetViaIndex(FRotator rotaionOffset, int totalInHandNum, int cardIndex)
{
	float middleNum = ((float)totalInHandNum + 1) / 2.f;
	float diff = (float)cardIndex + 1 - middleNum;

	return rotaionOffset * diff;;
}

bool FCardManager::GetInHandTransformPreset(int totalInHandNum, int cardIndex, FVector& pivotOffset, FRotator& rotationOffset, float& radius)
{
	FTransform trans;
	TArray<FCardTransformDataPreset*> allTrans;
	m_CardTransDataTable->GetAllRows<FCardTransformDataPreset>(FString(""), allTrans);
	for (int i = 0; i < allTrans.Num(); i++)
	{
		if (allTrans[i]->CardLocationType == ECardLocationType::InHand)
		{
			trans = allTrans[i]->CardTransform;
			break;
		}
	}

	bool foundTrans = false;
	TArray<FInHandCardTransOffsetPreset*> allOffset;
	m_InHandCardOffsetTable->GetAllRows<FInHandCardTransOffsetPreset>(FString(""), allOffset);
	FRotator offset;
	for (int j = 0; j < allOffset.Num(); ++j)
	{
		if (allOffset[j]->TotalNumberInHand == totalInHandNum)
		{
			rotationOffset = allOffset[j]->CardRotaionOffset;
			rotationOffset = GetOffsetViaIndex(rotationOffset, totalInHandNum, cardIndex);
			pivotOffset = allOffset[j]->CardPivotOffset;
			radius = allOffset[j]->Radius;
			foundTrans = true;
			break;
		}
	}

	return foundTrans;
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
	m_CardsInDeck.RemoveAt(drawingCardDeckIndex);
	
	SpawnCardActor(drawingCard);

	RearrangeCardsInHand();
}

void FCardManager::PlayerAddCardFromExternal(int cardID, ECardLocationType addTo)
{

}

void FCardManager::PlayerDiscardCard(int discardingCardInx)
{
	m_CardActors.RemoveAt(discardingCardInx);
	RearrangeCardsInHand();
}

ACardActor* FCardManager::SpawnCardActor(UCardBase* cardBase)
{
	FCardTransformData deckTrans = GetTransformData(ECardLocationType::Deck);
	ACardActor* spawnedActor = m_GMCache->GetWorld()->SpawnActor<ACardActor>(m_CardActorClass, deckTrans.CardTransform);
	m_CardActors.Insert(spawnedActor, 0);
	spawnedActor->CardTransformData = GetInHandTransformData(m_CardActors.Num(), 0);
	spawnedActor->Card = cardBase;

	m_GMCache->BattleScreenWidget->AddCardEventSpy(spawnedActor);

	return spawnedActor;
}

void FCardManager::AddEscapeCardInHand()
{
	//add unique escape card in hand,
	//if escape card already in hand, add debuff card
}

void FCardManager::RearrangeCardsInHand()
{
	for (int i = 0; i < m_CardActors.Num(); ++i)
	{
		ACardActor* cardActor = m_CardActors[i];
		if (cardActor != nullptr)
		{
			FCardTransformData newTrans = GetInHandTransformData(m_CardActors.Num(), i);
			cardActor->CardTransformTo(newTrans);
		}
	}
}

void FCardManager::SetCurFocusedCard_Internal(int cardIndex)
{
	if (cardIndex == m_CurFocusedInHandCardInx)
	{
		return;
	}

	int preInx = -1;
	int curInx = -1;
	for (int i = 0; i < m_CardActors.Num(); ++i)
	{
		ACardActor* cardActor = m_CardActors[i];
		if (cardActor == nullptr)
		{
			continue;
		}

		if (cardActor->CardTransformData.CardInHandIndex == m_CurFocusedInHandCardInx)
		{
			preInx = i;
			continue;
		}

		if (cardActor->CardTransformData.CardInHandIndex == cardIndex)
		{
			curInx = i;
			continue;
		}
	}

	if (preInx != -1)
	{
		ACardActor* cardActor = m_CardActors[preInx];
		if (cardActor != nullptr)
		{
			cardActor->OnCardLostFocus();
		}
	}

	if (curInx != -1)
	{
		ACardActor* cardActor = m_CardActors[curInx];
		if (cardActor != nullptr)
		{
			cardActor->OnCardFocused();
		}
	}

	m_CurFocusedInHandCardInx = cardIndex;
}

void FCardManager::SetCurFocusedCard(ACardActor* cardActor)
{
	if (cardActor == nullptr)
	{
		SetCurFocusedCard_Internal(-1);
	}
	else
	{
		int cardIndex = cardActor->CardTransformData.CardInHandIndex;
		SetCurFocusedCard_Internal(cardIndex);
	}
}

void FCardManager::SetCurSelectedCard_Internal(int cardIndex)
{
	if (cardIndex == m_CurSelectedInHandCardInx)
	{
		return;
	}

	int preInx = -1;
	int curInx = -1;
	for (int i = 0; i < m_CardActors.Num(); ++i)
	{
		ACardActor* cardActor = m_CardActors[i];
		if (cardActor == nullptr)
		{
			continue;
		}

		if (cardActor->CardTransformData.CardInHandIndex == m_CurSelectedInHandCardInx)
		{
			preInx = i;
			continue;
		}

		if (cardActor->CardTransformData.CardInHandIndex == cardIndex)
		{
			curInx = i;
			continue;
		}
	}

	if (preInx != -1)
	{
		ACardActor* cardActor = m_CardActors[preInx];
		if (cardActor != nullptr)
		{
			cardActor->OnCardUnselected();
		}
	}

	if (curInx != -1)
	{
		ACardActor* cardActor = m_CardActors[curInx];
		if (cardActor != nullptr)
		{
			cardActor->OnCardSelected();
			m_CurSelectedCard = cardActor;
		}
	}
	else
	{
		m_CurSelectedCard = NULL;
	}

	m_CurSelectedInHandCardInx = cardIndex;
}

void FCardManager::SetCurSelectedCard(ACardActor* cardActor)
{
	if (cardActor == nullptr)
	{
		SetCurSelectedCard_Internal(-1);
	}
	else
	{
		int cardIndex = cardActor->CardTransformData.CardInHandIndex;
		SetCurSelectedCard_Internal(cardIndex);
	}
}

//Test Functions
void FCardManager::Test_CreateDefaultCardsInDeck(int num)
{
	for (int i = 0; i < num; ++i)
	{
		UCardBase* newCard = CreateCardViaCardID(i);
		m_CardsInDeck.Add(newCard);
	}
}

#pragma optimize( "", on )