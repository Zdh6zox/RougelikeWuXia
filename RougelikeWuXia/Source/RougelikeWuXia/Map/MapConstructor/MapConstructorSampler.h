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

    void RunSampler() { RunSampler_Internal(); }
    bool IsFinished() const { return m_IsFinished; }
    void GetGeneratedMainNodes(TArray<FVector2D>& generatedNodes) const { generatedNodes = m_GeneratedMainNodeSamples; }
    void GetGeneratedSubNodes(TArray<FVector2D>& generatedNodes) const { generatedNodes = m_GeneratedMainNodeSamples; }

    virtual void RunSampler_Internal() = 0;

protected:
    bool CheckInsideMap(FVector2D newPoint) const;
    TArray<FVector2D> m_GeneratedMainNodeSamples;
    TArray<FVector2D> m_GeneratedSubNodeSamples;
    float m_MapSizeX;
    float m_MapSizeY;
    float m_NodeImpactRadius;
    int m_MainNodeNum;
    int m_SubNodeNum;
    int m_NumCandidates;
    bool m_IsFinished = false;
};

class ROUGELIKEWUXIA_API FMapConstructPoissonDiskSampler : public FMapConstructorSampler
{
public:
    FMapConstructPoissonDiskSampler(int mainNodeNum, float nodeImpactRadius, float mapSize_X, float mapSize_Y, int numCandidates)
        :FMapConstructorSampler(mainNodeNum, nodeImpactRadius, mapSize_X, mapSize_Y, numCandidates)
    {

    }
    FMapConstructPoissonDiskSampler(int subNodeNum, const TArray<FVector2D> mainNodes, float nodeImpactRadius, float mapSize_X, float mapSize_Y, int numCandidates)
        :FMapConstructorSampler(subNodeNum, mainNodes, nodeImpactRadius, mapSize_X, mapSize_Y, numCandidates)
    {
        m_ActivatedPoint.Append(mainNodes);
    }
    virtual void RunSampler_Internal() override;
private:
    bool IsValidPoint(FVector2D newPoint) const;
    FVector2D GenerateRandomPoint(FVector2D center);
    TArray<FVector2D> m_ActivatedPoint;
};

class ROUGELIKEWUXIA_API FMapConstructorBestCandidateSampler : public FMapConstructorSampler
{
public:
    virtual void RunSampler_Internal() override;
};

class ROUGELIKEWUXIA_API FMapConstructorRandomSampler : public FMapConstructorSampler
{
public:
    virtual void RunSampler_Internal() override;
};

class FCells
{
private:
    static const unsigned long NUM_2D_CELLS = 128;
    static const unsigned long NUM_CELLS = NUM_2D_CELLS * NUM_2D_CELLS;
    static const unsigned long NUM_OBJECTS_PER_CELL = 16;

    FVector2D m_Cells[NUM_CELLS][NUM_OBJECTS_PER_CELL];
    // buckets counts;
    unsigned long m_ObjectCount[NUM_CELLS];

    float  m_CellSize;
public:
    FCells() : m_CellSize(200.f) {}
    void Clear()
    {
        for (long i = 0; i < NUM_CELLS; i++)
        {
            m_ObjectCount[i] = 0;
        }
    }

    void AddPosition(FVector2D position);
    void Gather(FVector2D targetPosition, float radius, TArray<FVector2D>& locs);

private:
    void GetUVForPosition(FVector2D pos, long& u, long& v);
};