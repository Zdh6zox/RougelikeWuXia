// Fill out your copyright notice in the Description page of Project Settings.


#include "CardBase.h"
#include "Engine/Texture.h"
#include "Card/CardRuntimeData.h"
#include "Card/CardEnums.h"

UTexture* UCardBase::GetCardPic() const
{
    return m_CardDataCache.CardPic;
}

FText UCardBase::GetCardName() const
{
    return m_CardDataCache.CardName;
}

FText UCardBase::GetCardDescription() const
{
    return m_CardDataCache.CardDescription;
}

void UCardBase::InitializeFromCardData(FCardData& cardData)
{
	//m_RuntimeData->CardID = cardData.CardID;

    m_CardDataCache = cardData;
}

ECardType UCardBase::GetCardType() const
{
	return m_CardDataCache.CardType;
}

void UCardBase::InitializeFromCardRuntimeData(UCardRuntimeData* runtimeData)
{
	m_RuntimeData = runtimeData;
}