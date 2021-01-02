// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardTransformData.h"

class UCardBase;
class AGameManager;
class UDataTable;
/**
 * 
 */
class ROUGELIKEWUXIA_API FCardManager
{
public:
	void InitializeManager(AGameManager* gm);

    UCardBase* CreateCardViaCardID(uint32 cardID);

	FCardTransformData GetTransformData(ECardLocationType locationType, int totalInHandNum, int cardIndex);

private:
	UDataTable* m_CardTransDataTableMap;
	AGameManager* m_GMCache;
    TArray<UCardBase*> m_ExistingCards;
};
