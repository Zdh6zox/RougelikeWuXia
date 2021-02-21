// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardRuntimeData.generated.h"

/**
 * 
 */
UCLASS()
class ROUGELIKEWUXIA_API UCardRuntimeData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		TMap<int, int> OwnedEffects;

private:

};
