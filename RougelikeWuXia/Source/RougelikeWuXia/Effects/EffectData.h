// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectType.h"
#include "EffectData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FEffectData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		EEffectType EffectType;

	UPROPERTY(EditAnywhere)
		int LastRoundNumber;
};
