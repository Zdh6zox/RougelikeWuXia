// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CardEnums.h"
#include "CardTransTableMap.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FCardTransTableMap : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		ECardLocationType CardLocationType;

	UPROPERTY(EditAnywhere)
		int TotalCardNumOnHand;

	UPROPERTY(EditAnywhere)
		UDataTable* CardTransTable;
};
