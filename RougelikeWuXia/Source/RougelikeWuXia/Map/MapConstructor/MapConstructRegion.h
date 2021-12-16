// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FMapConstructRegion
{
public:
    bool IsInsideRegion(FVector2D testingLoc);

    FVector2D RegionCenter;
    TArray<FVector2D> RegionVertices;
};
