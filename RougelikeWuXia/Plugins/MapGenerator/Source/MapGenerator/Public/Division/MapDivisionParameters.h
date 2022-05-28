// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map2DBorder.h"
/**
 * 
 */
enum MAPGENERATOR_API EMap2DDivisionMethodType
{
    invalid,
    VoronoiDiagram
};

class MAPGENERATOR_API FMap2DDivisionParameters
{
public:
    FMap2DDivisionParameters(EMap2DDivisionMethodType methodType, const FMap2DBorder& mapBorder)
    {
        checkf(methodType != EMap2DDivisionMethodType::invalid, TEXT("illegal division parameter constructed"));
        m_MapBorder = mapBorder;
    }
    FMap2DDivisionParameters(EMap2DDivisionMethodType methodType, const FMap2DBorder& mapBorder, const TArray<FVector2D>& regionOrigins)
    {
        checkf(methodType == EMap2DDivisionMethodType::VoronoiDiagram, TEXT("illegal division parameter constructed"));
        m_MapBorder = mapBorder;
        m_RegionOrigins = regionOrigins;
    }

private:
    FMap2DBorder m_MapBorder;
    TArray<FVector2D> m_RegionOrigins;
};
