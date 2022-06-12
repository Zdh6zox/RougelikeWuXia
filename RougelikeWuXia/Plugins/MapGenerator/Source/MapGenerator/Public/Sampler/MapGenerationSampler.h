// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map2DSampleSettings.h"
/**
 * 
 */
class MAPGENERATOR_API IMapGenerationSampler
{
public:
    virtual void SampleIn2DMap(const FMap2DSampleSettings& sampleSettings, TArray<FVector2D>& postionSamples) = 0;
};
