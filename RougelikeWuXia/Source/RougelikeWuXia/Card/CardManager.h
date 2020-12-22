// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UCardBase;
class AGameManager;
/**
 * 
 */
class ROUGELIKEWUXIA_API FCardManager
{
public:
	void InitializeManager(AGameManager* gm);

    UCardBase* CreateCardViaCardID(uint32 cardID);

private:
	AGameManager* m_GMCache;
    TArray<UCardBase*> m_ExistingCards;
};
