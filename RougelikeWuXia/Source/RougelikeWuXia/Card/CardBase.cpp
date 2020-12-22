// Fill out your copyright notice in the Description page of Project Settings.


#include "CardBase.h"
#include "Engine/Texture.h"

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

void UCardBase::InitializeFromCardData(FCardData cardData)
{
    m_CardDataCache = cardData;
}