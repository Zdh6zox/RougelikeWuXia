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
    void SampleIn2DMap(const FMap2DSampleSettings& sampleSettings, TArray<FVector2D>& postionSamples);

private:
    FVector2D GenerateRandomPoint(FVector2D center, const TArray<FVector2D>& existingPoints);
    FMap2DSampleSettings m_SampleSettings;
    TArray<FVector2D> m_ActivatedPoint;
    TArray<FVector2D> m_GeneratedNodeSamples;
};
