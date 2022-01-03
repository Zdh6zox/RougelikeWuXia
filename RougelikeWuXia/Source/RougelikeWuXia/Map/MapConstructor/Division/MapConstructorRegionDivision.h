// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/MapConstructor/Division/VoronoiDiagram/VoronoiDiagramGeneratedSite.h"
#include "Map/MapConstructor/Division/VoronoiDiagram/VoronoiDiagramGeneratedEdge.h"
#include "Map/MapConstructor/MapConstructRegion.h"

class FMapConstructDebugger;
class FVoronoiDiagram;

class FMapConstructorRegionDivision
{
public:
    void AttachDebugger(FMapConstructDebugger* debugger);

protected:
    FMapConstructDebugger* m_Debugger = nullptr;
};

class FRegionDivision_VoronoiDiagram : public FMapConstructorRegionDivision
{
public:
    FRegionDivision_VoronoiDiagram(FBox2D InBounds);

    void AddPointsForDiagramGeneration(const TArray<FVector2D>& points);
    void GenerateDiagram(int32 RelaxationCycles);
    void GetGeneratedRegions(TArray<FMapConstructRegion>& generatedRegion);
    void GetGeneratedSites(TArray<FVoronoiDiagramGeneratedSite>& generatedSites);

private:
    TSharedPtr<FVoronoiDiagram> m_VoronoDiagram;
    FBox2D m_Bounds;
};
