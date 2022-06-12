// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerator2DSetting.h"
/**
 * 
 */
class FMap2DSampleSettings
{
public:
    FMap2DSampleSettings() {}
    FMap2DSampleSettings(const FMapGenerator2DSetting& settings)
    {
        m_MainNodeCount = settings.MainNodeCount;
        m_SubNodeCount = settings.SubNodeCount;
        m_MainNodeRadius = settings.MainNodeImpactRadius;
        m_SubNodeRadius = settings.SubNodeImpactRadius;
    }
private:

    int m_MainNodeCount;
    int m_SubNodeCount;
    float m_MainNodeRadius;
    float m_SubNodeRadius;
};
