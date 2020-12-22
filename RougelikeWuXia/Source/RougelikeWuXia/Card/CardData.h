// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Card/CardEnums.h"
#include "Effects/EffectData.h"
#include "CardData.generated.h"

/**
 * 
 */
class UTexture;
USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FCardData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		uint32 CardID;

    UPROPERTY(EditAnywhere)
        ECardType CardType;

	UPROPERTY(EditAnywhere)
		FText CardName;

    UPROPERTY(EditAnywhere)
        UTexture* CardPic;

	UPROPERTY(EditAnywhere)
		bool IsComposite;

	UPROPERTY(EditAnywhere)
		TArray<uint32> CompositeFormula;

	UPROPERTY(EditAnywhere)
		ECardNatureType NatureType;

	UPROPERTY(EditAnywhere) 
        FText CardDescription;
};

USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FSkillCardData : public FCardData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<FEffectData> EffectData;
};