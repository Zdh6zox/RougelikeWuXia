// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapConstructData.h"

/**
 * 
 */
class UMapData;

class ROUGELIKEWUXIA_API FMapConstructor
{
public:
	UMapData* ConstructMap(FMapConstructData& constructingData);
};
