// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBPFunctionLibrary.h"
#include "Card/CardBase.h"
#include "Managers/GameManager.h"
#include "Managers/BattleManager.h"
#include "Card/CardManager.h"
#include "RougelikeWuXia.h"

UCardBase* UGameBPFunctionLibrary::CreateNewCard(UObject* outer, int cardID)
{
    if (outer == nullptr)
    {
        UE_LOG(LogMain, Error, TEXT("outer cannot be null!"));
        return nullptr;
    }

    UWorld* world = outer->GetWorld();
    if (world == nullptr)
    {
        UE_LOG(LogMain, Error, TEXT("world cannot be found!"));
        return nullptr;
    }

    AGameManager* gm = GetGameManager(world);
    return gm->GetCardManager().CreateCardViaCardID((uint32)cardID);
}

AGameManager* UGameBPFunctionLibrary::GetGameManager(UWorld* world)
{
    return AGameManager::GetGameManager(world);
}