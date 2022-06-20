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
    FMap2DRegion(FVector2D regionOrigin, const TArray<class FMap2DEdge>& edges);
    //FMap2DRegion& operator= (const FMap2DRegion& rhs);

    bool IsInsideRegion(FVector2D testingPos, bool includingBorder = false, float borderThickness = 0.0f) const;
    FVector2D GetRegionOrigin() const { return m_Origin; }
    TArray<FVector2D> GetRegionVertices() const { return m_Vertices; }
    TArray<class FMap2DEdge> GetRegionEdges() const { return m_Edges; }
    static FMap2DRegion GetRegionFromBorder(const FMap2DBorder& border);

private:
    FVector2D m_Origin;
    TArray<class FMap2DEdge> m_Edges;
    TArray<FVector2D> m_Vertices;
};
