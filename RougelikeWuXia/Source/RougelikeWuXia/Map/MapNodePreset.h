// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MapEnums.h"
#include "MapNodePreset.generated.h"
/**
 * 
 */
class AMapNodeActor;
class AMapNodeLinkActor;

USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FMapNodePresetUnit
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere)
        TSubclassOf<AMapNodeActor> NodeTemplate;

    UPROPERTY(EditAnywhere)
        FTransform RelativeTrans;
};

USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FMapNodePresetLink
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere)
        TSubclassOf<AMapNodeLinkActor> LinkTemplate;

    UPROPERTY(EditAnywhere)
        int StartIndex;

    UPROPERTY(EditAnywhere)
        int EndIndex;
};

USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FImpactRadiusRatePair
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Radius;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.0f, ClampMax = 1.0f))
		float Rate = 0.0f;
};

USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FMapPresetImpactRadius
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		EMapConstructUnitRarenessType Rareness;

	UPROPERTY(EditAnywhere)
		TArray<FImpactRadiusRatePair> RadiusPossibilities;
};

USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FMapNodePreset : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere)
        TArray<FMapNodePresetUnit> Units;

    UPROPERTY(EditAnywhere)
        TArray<FMapNodePresetLink> Links;

	UPROPERTY(EditAnywhere)
		TArray<FMapPresetImpactRadius> PresetImpactRadiusList;

	UPROPERTY(EditAnywhere)
		EMapConstructUnitRarenessType Rareness;
};
