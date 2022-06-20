// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map2DSampleSettings.h"
#include "Map2DRegion.h"
/**
 * 
 */
class MAPGENERATOR_API IMapGenerationSampler
{
public:
    virtual ~IMapGenerationSampler() {}
    virtual void SampleIn2DMap(const FMap2DSampleSettings& sampleSettings, TArray<FVector2D>& postionSamples) = 0;
    virtual void SampleInRegion(const FMap2DSampleSettings& sampleSettings, const FMap2DRegion& region, TArray<FVector2D>& postionSamples) = 0;
};
