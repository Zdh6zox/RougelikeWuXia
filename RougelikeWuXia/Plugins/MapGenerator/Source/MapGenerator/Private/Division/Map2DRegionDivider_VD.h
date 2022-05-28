// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGeneratorRegionDivider.h"

/**
 * 
 */
class FMap2DRegionDivider_VD : public IMapGeneratorRegionDivider
{
public:
    void Divide2DMap(FMap2DDivisionParameters divisionParams, TArray<FMap2DRegion>& generatedRegions) const override;
};
