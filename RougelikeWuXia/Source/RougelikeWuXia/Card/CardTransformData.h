// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardEnums.h"
#include "CardTransformData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FCardTransformData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		int CardInHandIndex;

	UPROPERTY(EditAnywhere)
		ECardLocationType CardLocationType;

	UPROPERTY(EditAnywhere)
		FTransform CardTransform;
};