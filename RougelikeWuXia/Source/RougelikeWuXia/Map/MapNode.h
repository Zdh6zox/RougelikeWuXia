// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MapNode.generated.h"

/**
 * 
 */
class AMapNodeActor;
USTRUCT()
struct ROUGELIKEWUXIA_API FMapNodeStatic
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		uint32 NodeIndex;

	UPROPERTY()
		TArray<uint32> AccessableNodes;

	UPROPERTY()
		FVector2D NodeCoordinate;

	UPROPERTY()
		TSubclassOf<AMapNodeActor> NodeTemplate;
};

UCLASS()
class ROUGELIKEWUXIA_API UMapNode : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		FMapNodeStatic StaticData;
};
