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
	UPROPERTY(EditAnywhere, DisplayName = "Max Map Nodes Count")
		uint32 MaxMapNodeCount;

	UPROPERTY(EditAnywhere, DisplayName = "Min Map Nodes Count")
		uint32 MinMapNodeCount;

	UPROPERTY(EditAnywhere, DisplayName = "Max Node Links Count")
		uint32 MaxNodeLinksCount;

    UPROPERTY(EditAnywhere, DisplayName = "Max Main Nodes Count")
        uint32 MaxMainNodeCount;

    UPROPERTY(EditAnywhere, DisplayName = "Max Sub Nodes Count")
        uint32 MaxSubNodeCount;

    UPROPERTY(EditAnywhere, DisplayName = "Main Node Radius")
        float MainNodeRadius;

    UPROPERTY(EditAnywhere, DisplayName = "Sub Node Radius")
        float SubNodeRadius;

	UPROPERTY(EditAnywhere)
		FVector2D MapSize;
};
