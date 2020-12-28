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

FWidgetTransform UGameBPFunctionLibrary::LerpWidgetTransform(FWidgetTransform currentTrans, FWidgetTransform targetTrans, float ratio)
{
	FVector2D newTranslation = FMath::Lerp(currentTrans.Translation, targetTrans.Translation, ratio);
	FVector2D newShear = FMath::Lerp(currentTrans.Shear, targetTrans.Shear, ratio);
	FVector2D newScale = FMath::Lerp(currentTrans.Scale, targetTrans.Scale, ratio);
	float newAngle = FMath::Lerp(currentTrans.Angle, targetTrans.Angle, ratio);

	return FWidgetTransform(newTranslation, newScale, newShear, newAngle);
}

bool UGameBPFunctionLibrary::WidgetTransformEqual(const FWidgetTransform& a, const FWidgetTransform& b)
{
	return a == b;
}