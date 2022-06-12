// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator2D.h"
#include "Division/MapGeneratorRegionDivider.h"
#include "Division/MapDivisionParameters.h"

void FMapGenerator2D::Construct2DMap(FMap2DGenerationResult& generationResult)
{
    FMap2DBorder border(m_GenerationSetting.Map2DSizeLength, m_GenerationSetting.Map2DSizeWidth);

    //FMap2DDivisionParameters* vdParameters = new FMap2DDivisionParameters(EMap2DDivisionMethodType::VoronoiDiagram,*border)
}