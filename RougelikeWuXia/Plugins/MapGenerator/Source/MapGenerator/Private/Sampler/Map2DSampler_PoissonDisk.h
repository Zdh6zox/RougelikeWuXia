// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerationSampler.h"
/**
 * 
 */
class FMap2DSampler_PoissonDisk : public IMapGenerationSampler
{
public:
    ~FMap2DSampler_PoissonDisk() override {}
    void SampleIn2DMap(const FMap2DSampleSettings& sampleSettings, TArray<FVector2D>& postionSamples);
    void SampleInRegion(const FMap2DSampleSettings& sampleSettings, const FMap2DRegion& region, TArray<FVector2D>& postionSamples);

private:
    FVector2D GenerateRandomPoint_CenterBased(FVector2D center, float impactRadius);
    FVector2D GenerateRandomPoint_CoordinateBased(float minX, float minY, float maxX, float maxY);
    bool IsValidPoint(FVector2D newPoint, float impactRadius) const;
    FMap2DSampleSettings m_SampleSettings;
    FMap2DRegion m_Region;
    TArray<FVector2D> m_ActivatedPoint;
    TArray<FVector2D> m_GeneratedNodeSamples;
};
