// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardEnums.h"
#include "Engine/DataTable.h"
#include "CardTransformDataPreset.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FCardTransformDataPreset : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		ECardLocationType CardLocationType;

	UPROPERTY(EditAnywhere)
		FTransform CardTransform;
};

USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FInHandCardTransOffsetPreset : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		int TotalNumberInHand;

	UPROPERTY(EditAnywhere)
		FVector CardPivotOffset;

	UPROPERTY(EditAnywhere)
		float Radius;

	UPROPERTY(EditAnywhere)
		FRotator CardRotaionOffset;
};
