// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MapNodeLink.generated.h"

/**
 * 
 */
USTRUCT()
struct ROUGELIKEWUXIA_API FMapNodeLinkStatic
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		uint32 FirstNodeIndex;

	UPROPERTY()
		uint32 SecondNodeIndex;
};

UCLASS()
class ROUGELIKEWUXIA_API UMapNodeLink : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		FMapNodeLinkStatic StaticData;
};
