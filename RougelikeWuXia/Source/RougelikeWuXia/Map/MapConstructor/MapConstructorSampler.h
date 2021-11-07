// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ROUGELIKEWUXIA_API FMapConstructorSampler
{
public:
    FMapConstructorSampler(int mainNodeNum, float nodeImpactRadius, float mapSize_X, float mapSize_Y, int numCandidates)
        : m_MapSizeX(mapSize_X), m_MapSizeY(mapSize_Y), m_MainNodeNum(mainNodeNum), m_NodeImpactRadius(nodeImpactRadius), m_NumCandidates(numCandidates)
    {
        m_GeneratedMainNodeSamples.Reserve(mainNodeNum);
    }

    FMapConstructorSampler(int subNodeNum, const TArray<FVector2D> mainNodes, float nodeImpactRadius, float mapSize_X, float mapSize_Y, int numCandidates)
        : m_MapSizeX(mapSize_X), m_MapSizeY(mapSize_Y), m_SubNodeNum(subNodeNum), m_NodeImpactRadius(nodeImpactRadius), m_NumCandidates(numCandidates)
    {
        m_GeneratedMainNodeSamples.Empty();
        m_GeneratedMainNodeSamples.Append(mainNodes);
        m_GeneratedSubNodeSamples.Reserve(subNodeNum);
    }

    void RunSampler() { RunSampler(); }
    void GetGeneratedMainNodes(TArray<FVector2D>& generatedNodes) { generatedNodes = m_GeneratedMainNodeSamples; }
    void GetGeneratedSubNodes(TArray<FVector2D>& generatedNodes) { generatedNodes = m_GeneratedMainNodeSamples; }

    virtual void RunSampler_Internal() const = 0;

protected:
    TArray<FVector2D> m_GeneratedMainNodeSamples;
    TArray<FVector2D> m_GeneratedSubNodeSamples;
    float m_MapSizeX;
    float m_MapSizeY;
    float m_NodeImpactRadius;
    int m_MainNodeNum;
    int m_SubNodeNum;
    int m_NumCandidates;
};

class ROUGELIKEWUXIA_API FMapConstructPoissonDiskSampler : public FMapConstructorSampler
{
public:
    virtual void RunSampler_Internal();
private:
    FVector2D GenerateRandomPoint(FVector2D center);
    TArray<FVector2D> m_ActivedPoint;
};

class ROUGELIKEWUXIA_API FMapConstructorBestCandidateSampler : public FMapConstructorSampler
{
public:
    virtual void RunSampler_Internal();
};

class ROUGELIKEWUXIA_API FMapConstructorRandomSampler : public FMapConstructorSampler
{
public:
    virtual void RunSampler_Internal();
};