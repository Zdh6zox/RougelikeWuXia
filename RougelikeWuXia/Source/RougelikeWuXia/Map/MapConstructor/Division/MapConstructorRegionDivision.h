// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VoronoiDiagram/VoronoiDiagramGeneratedSite.h"

class FVoronoiDiagram;

class FMapConstructorRegionDivision
{
};

class FRegionDivision_VoronoiDiagram : public FMapConstructorRegionDivision
{
public:
    FRegionDivision_VoronoiDiagram(FBox2D InBounds);

    void AddPointsForDiagramGeneration(const TArray<FVector2D>& points);
    void GenerateDiagram(int32 RelaxationCycles);
    void GetGeneratedSites(TArray<FVoronoiDiagramGeneratedSite>& generatedSites);

private:
    TSharedPtr<FVoronoiDiagram> m_VoronoDiagram;
    FBox2D m_Bounds;
};
