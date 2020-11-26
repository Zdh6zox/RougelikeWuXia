// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardData.h"
#include "CardBase.generated.h"

/**
 * 
 */
UCLASS()
class ROUGELIKEWUXIA_API UCardBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, category = "Card Basic")
		int CardID;

private:
	FCardData* m_CardDataCache;
};
