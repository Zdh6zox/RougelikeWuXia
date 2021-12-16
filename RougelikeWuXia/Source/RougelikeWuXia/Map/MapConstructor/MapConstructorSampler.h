// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapConstructRegion.h"
/**
 * 
 */
class AActor;

class FMapConstructorSampler
{
public:
    virtual void GetGeneratedNodes(TArray<FVector2D>& nodes) {}
    void RunSampler() { RunSampler_Internal(); }
    bool IsFinished() const { return m_IsFinished; }
    virtual void ShowDebug(AActor* mapActor) = 0;

    virtual void RunSampler_Internal() = 0;

protected:
    bool m_IsFinished = false;
};

class FMapConstructPoissonDiskSampler : public FMapConstructorSampler
{
public:
    FMapConstructPoissonDiskSampler(int nodeNum, float nodeImpactRadius, float mapSize_X, float mapSize_Y, int numCandidates)
    {
        m_NodeNum = nodeNum;
        m_ImpactRadius = nodeImpactRadius;
        m_MapSizeX = mapSize_X;
        m_MapSizeY = mapSize_Y;
        m_NumCandidates = numCandidates;
    }

    virtual void RunSampler_Internal() override;
    virtual void ShowDebug(AActor* mapActor) override;
    virtual void GetGeneratedNodes(TArray<FVector2D>& nodes) override;

private:
    void SampleNodes();
    bool IsValidPoint(FVector2D newPoint) const;
    FVector2D GenerateRandomPoint(FVector2D center);
    bool CheckInsideMap(FVector2D newPoint) const;

    TArray<FVector2D> m_ActivatedPoint;
    TArray<FVector2D> m_GeneratedNodeSamples;
    float m_MapSizeX;
    float m_MapSizeY;
    float m_ImpactRadius;
    int m_NodeNum;
    int m_NumCandidates;
};

class FMapConstructPoissonDiskWithRegionSampler : public FMapConstructorSampler
{
public:
    FMapConstructPoissonDiskWithRegionSampler(int nodeNum, float nodeImpactRadius, const TArray<FMapConstructRegion>& regions, int numCandidates)
    {
        m_MaxRegionNodeNum = nodeNum;
        m_ImpactRadius = nodeImpactRadius;
        m_Regions = regions;
        m_NumCandidates = numCandidates;
    }

    virtual void RunSampler_Internal() override;
    virtual void ShowDebug(AActor* mapActor) override;
    virtual void GetGeneratedNodes(TArray<FVector2D>& nodes) override;

private:
    void GenerateNodesInsideRegion(FMapConstructRegion region);
    FVector2D GenerateRandomPoint(FVector2D center);
    bool IsValidPoint(FVector2D newPoint, FMapConstructRegion region, const TArray<FVector2D>& generatedLocs) const;

    int m_CurRegionNodeNum;
    int m_MaxRegionNodeNum;
    float m_ImpactRadius;
    TArray<FMapConstructRegion> m_Regions;
    TArray<FVector2D> m_GeneratedNodeSamples;
    TArray<FVector2D> m_ActivatedNodes;
    int m_NumCandidates;
    int m_CurRegionIndex;
};

class FMapConstructorBestCandidateSampler : public FMapConstructorSampler
{
public:
    virtual void RunSampler_Internal() override;
    virtual void ShowDebug(AActor* mapActor) override;
};

class FMapConstructorRandomSampler : public FMapConstructorSampler
{
public:
    virtual void RunSampler_Internal() override;
    virtual void ShowDebug(AActor* mapActor) override;
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