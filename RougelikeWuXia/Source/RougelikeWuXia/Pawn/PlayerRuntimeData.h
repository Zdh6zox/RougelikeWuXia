// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerRuntimeData.generated.h"

class UCardRuntimeData;
/**
 * 
 */
UCLASS()
class ROUGELIKEWUXIA_API UPlayerRuntimeData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		int Strength;

	UPROPERTY()
		int Agility;

	UPROPERTY()
		int InnerStrength;

	UPROPERTY()
		int Intelligence;

	UPROPERTY()
		int Instinct;

	UPROPERTY()
		int Luckiness;

	UPROPERTY()
		TArray<UCardRuntimeData*> PlayerOwnedCards;


};
