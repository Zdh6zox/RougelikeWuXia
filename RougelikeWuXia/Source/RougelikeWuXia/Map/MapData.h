// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MapNode.h"
#include "MapNodeLink.h"
#include "MapData.generated.h"

/**
 * 
 */
USTRUCT()
struct ROUGELIKEWUXIA_API FMapDataStatic
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		uint32 MapNodeCount;

	UPROPERTY()
		float MapLength;

	UPROPERTY()
		float MapWidth;

	UPROPERTY()
		TArray<FMapNodeStatic> NodeStaticArray;

	UPROPERTY()
		TArray<FMapNodeLinkStatic> NodeLinkStaticArray;
};

UCLASS()
class ROUGELIKEWUXIA_API UMapData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
		TArray<UMapNode*> Nodes;

	UPROPERTY()
		TArray<UMapNodeLink*> Links;

public:
	void GatherMapStaticData(FMapDataStatic& staticMapData);
};
