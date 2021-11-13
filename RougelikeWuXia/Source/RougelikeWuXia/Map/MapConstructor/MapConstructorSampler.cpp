// Fill out your copyright notice in the Description page of Project Settings.


#include "MapConstructorSampler.h"
#include "DrawDebugHelpers.h"

#pragma optimize("",off)
bool FMapConstructorSampler::CheckInsideMap(FVector2D newPoint) const
{
    return newPoint.X <= m_MapSizeX && newPoint.X >= 0.0f
        && newPoint.Y <= m_MapSizeY && newPoint.Y >= 0.0f;
}

FVector2D FMapConstructPoissonDiskSampler::GenerateRandomPoint(FVector2D center)
{
    //find a random point inside circle ring which inner radius r outer radius 2r
    float randomAngle = FMath::RandRange(0.0f, 360.f);
    float randomRadius = FMath::RandRange(m_NodeImpactRadius, 2 * m_NodeImpactRadius);

    FVector2D rotatingVec = FVector2D(1.0f, 0.0f);
    FVector2D randomVec = rotatingVec.GetRotated(randomAngle);

    return center + randomVec * randomRadius;
}

void FMapConstructPoissonDiskSampler::RunSampler_Internal()
{
    //generate first activated point if empty
    if (m_ActivatedPoint.Num() == 0)
    {
        float ranX = FMath::RandRange(0.0, m_MapSizeX);
        float ranY = FMath::RandRange(0.0, m_MapSizeY);
        m_GeneratedMainNodeSamples.Add(FVector2D(ranX, ranY));
        m_ActivatedPoint.Add(FVector2D(ranX, ranY));
    }

    while (m_ActivatedPoint.Num() > 0
        && m_GeneratedMainNodeSamples.Num() < m_MainNodeNum)
    {
        //random pick one activated point
        int activatedPntInx = FMath::RandRange(0, m_ActivatedPoint.Num() - 1);
        FVector2D activatedPoint = m_ActivatedPoint[activatedPntInx];
        
        int remainSamplingCount = m_NumCandidates;
        while (remainSamplingCount > 0)
        {
            FVector2D newCandidate = GenerateRandomPoint(activatedPoint);
            if (IsValidPoint(newCandidate))
            {
                m_ActivatedPoint.Add(newCandidate);
                m_GeneratedMainNodeSamples.Add(newCandidate);
                break;
            }
            remainSamplingCount--;
        }

        //no valid point generated, remove it from activated point list
        if (remainSamplingCount == 0)
        {
            m_ActivatedPoint.Remove(activatedPoint);
        }
    }

    m_IsFinished = true;
}

bool FMapConstructPoissonDiskSampler::IsValidPoint(FVector2D newPoint) const
{
    if (!CheckInsideMap(newPoint))
    {
        return false;
    }

    //[TODO]Use object bucket to optimize
    for (int i = 0; i < m_GeneratedMainNodeSamples.Num(); ++i)
    {
        FVector2D testingPoint = m_GeneratedMainNodeSamples[i];
        float distance = FVector2D::Distance(testingPoint, newPoint);
        if (distance <= m_NodeImpactRadius)
        {
            return false;
        }
    }

    return true;
}

void FMapConstructorBestCandidateSampler::RunSampler_Internal()
{

}

void FMapConstructorRandomSampler::RunSampler_Internal()
{

}

#pragma optimize("",on)