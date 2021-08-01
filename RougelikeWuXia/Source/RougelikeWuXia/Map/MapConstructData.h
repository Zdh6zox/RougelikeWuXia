// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapConstructData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FMapConstructData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(DisplayName = "Max Map Nodes Count")
		uint32 MaxMapModeCount;

	UPROPERTY(DisplayName = "Min Map Nodes Count")
		uint32 MinMapModeCount;

	UPROPERTY(DisplayName = "Max Node Links Count")
		uint32 MaxNodeLinksCount;

	UPROPERTY()
		FVector2D MapSize;
};
