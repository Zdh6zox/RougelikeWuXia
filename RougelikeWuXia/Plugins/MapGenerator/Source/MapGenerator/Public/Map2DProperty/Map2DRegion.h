// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FMap2DEdge;
class MAPGENERATOR_API FMap2DRegion
{
public:
    FMap2DRegion(FVector2D regionOrigin, const TArray<class FMap2DEdge>& edges)
    {
        m_Origin = regionOrigin;
        m_Edges = edges;
    }

    bool IsInsideRegion(FVector2D testingPos, bool includingBorder = false) const;

private:
    FVector2D m_Origin;
    TArray<class FMap2DEdge> m_Edges;
};
