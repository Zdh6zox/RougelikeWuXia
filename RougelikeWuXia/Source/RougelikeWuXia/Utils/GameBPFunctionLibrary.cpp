// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBPFunctionLibrary.h"
#include "Card/CardBase.h"

UCardBase* UGameBPFunctionLibrary::CreateNewCard(UObject* outer, FCardData data)
{
    UCardBase* newCard = NewObject<UCardBase>(outer, UCardBase::StaticClass(), NAME_None);
    newCard->InitializeFromCardData(data);
    return newCard;
}