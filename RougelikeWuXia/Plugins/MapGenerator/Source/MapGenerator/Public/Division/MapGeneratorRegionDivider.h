// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapDivisionParameters.h"
#include "Map2DRegion.h"
/**
 * 
 */
class FMap2DDivisionParameters;
class MAPGENERATOR_API IMapGeneratorRegionDivider
{
public:
    virtual void Divide2DMap(FMap2DDivisionParameters divisionParams, TArray<FMap2DRegion>& generatedRegions) const = 0;
};
