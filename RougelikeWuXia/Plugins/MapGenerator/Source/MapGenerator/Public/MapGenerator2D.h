// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerator2DSetting.h"
#include "Map2DGenerationResult.h"
/**
 * 
 */
class IMapGeneratorRegionDivider;
class MAPGENERATOR_API FMapGenerator2D
{
public:
    FMapGenerator2D(const FMapGenerator2DSetting& generationSetting)
        : m_GenerationSetting(generationSetting)
    {
    }

    void Construct2DMap(FMap2DGenerationResult& generationResult);

private:
    FMapGenerator2D(){}

    FMapGenerator2DSetting m_GenerationSetting;
    IMapGeneratorRegionDivider* m_RegionDivider = nullptr;
};
