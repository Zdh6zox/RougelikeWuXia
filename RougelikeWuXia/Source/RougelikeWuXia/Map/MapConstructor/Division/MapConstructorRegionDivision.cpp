// Fill out your copyright notice in the Description page of Project Settings.


#include "MapConstructorRegionDivision.h"
#include "RougelikeWuXia.h"
#include "Map/MapConstructor/Division/VoronoiDiagram/VoronoiDiagram.h"

FRegionDivision_VoronoiDiagram::FRegionDivision_VoronoiDiagram(FBox2D InBounds)
{
    m_VoronoDiagram = MakeShared<FVoronoiDiagram>(InBounds);
}

void FRegionDivision_VoronoiDiagram::AddPointsForDiagramGeneration(const TArray<FVector2D>& points)
{
    m_VoronoDiagram->AddPoints(points);
}

void FRegionDivision_VoronoiDiagram::GenerateDiagram(int32 RelaxationCycles)
{
    m_VoronoDiagram->GenerateSites(RelaxationCycles);
}

void FRegionDivision_VoronoiDiagram::GetGeneratedSites(TArray<FVoronoiDiagramGeneratedSite>& generatedSites)
{
    for (auto it(m_VoronoDiagram->GeneratedSites.CreateConstIterator()); it; it++)
    {

    }
}