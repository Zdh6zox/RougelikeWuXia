// Fill out your copyright notice in the Description page of Project Settings.


#include "Sampler/Map2DSampler_PoissonDisk.h"
#include "RandomGenerateManager.h"

void FMap2DSampler_PoissonDisk::SampleIn2DMap(const FMap2DSampleSettings& sampleSettings, TArray<FVector2D>& postionSamples)
{
    m_SampleSettings = sampleSettings;

    m_ActivatedPoint.Empty();
    m_GeneratedNodeSamples.Empty();
    FMap2DBorder border = sampleSettings.GetBorder();
    m_Region = FMap2DRegion::GetRegionFromBorder(border);

    //Generate first point as a base point
    FVector2D firstPnt = GenerateRandomPoint_CoordinateBased(0.0f, 0.0f, border.GetMapLength(), border.GetMapWidth());
    m_ActivatedPoint.Add(firstPnt);
    m_GeneratedNodeSamples.Add(firstPnt);

    float impactRadius = m_SampleSettings.m_MainNodeRadius;
    while (m_ActivatedPoint.Num() > 0
        && m_GeneratedNodeSamples.Num() < sampleSettings.m_MainNodeCount)
    {
        //random pick one activated point
        int activatedPntInx = FRandomGenerateManager::GetInstance()->RandRange_Int(0, m_ActivatedPoint.Num() - 1);
        FVector2D activatedPoint = m_ActivatedPoint[activatedPntInx];

        int remainSamplingCount = m_SampleSettings.m_IterationCandidateNum;
        while (remainSamplingCount > 0)
        {
            FVector2D newCandidate = GenerateRandomPoint_CenterBased(activatedPoint, impactRadius);
            if (IsValidPoint(newCandidate, impactRadius))
            {
                m_ActivatedPoint.Add(newCandidate);
                m_GeneratedNodeSamples.Add(newCandidate);
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

    postionSamples = m_GeneratedNodeSamples;
}

void FMap2DSampler_PoissonDisk::SampleInRegion(const FMap2DSampleSettings& sampleSettings, const FMap2DRegion& region, TArray<FVector2D>& postionSamples)
{
    m_SampleSettings = sampleSettings;

    m_ActivatedPoint.Empty();
    m_GeneratedNodeSamples.Empty();
    m_Region = m_Region;

    m_ActivatedPoint.Add(region.GetRegionOrigin());

    float impactRadius = m_SampleSettings.m_SubNodeRadius;
    while (m_ActivatedPoint.Num() > 0
        && m_GeneratedNodeSamples.Num() < m_SampleSettings.m_SubNodeCount)
    {
        //random pick one activated point
        int activatedPntInx = FRandomGenerateManager::GetInstance()->RandRange_Int(0, m_ActivatedPoint.Num() - 1);
        FVector2D activatedPoint = m_ActivatedPoint[activatedPntInx];

        int remainSamplingCount = m_SampleSettings.m_IterationCandidateNum;;
        while (remainSamplingCount > 0)
        {
            FVector2D newCandidate = GenerateRandomPoint_CenterBased(activatedPoint, impactRadius);
            if (IsValidPoint(newCandidate, impactRadius))
            {
                m_ActivatedPoint.Add(newCandidate);
                m_GeneratedNodeSamples.Add(newCandidate);
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

    postionSamples = m_GeneratedNodeSamples;
}

FVector2D FMap2DSampler_PoissonDisk::GenerateRandomPoint_CenterBased(FVector2D center, float impactRadius)
{
    float randomAngle = FRandomGenerateManager::GetInstance()->RandRange_Float(0.0f, 360.0f, ERandomMethodType::Normal);
    float randomRadius = FRandomGenerateManager::GetInstance()->RandRange_Float(impactRadius, impactRadius * 2, ERandomMethodType::Normal);

    FVector2D vecX = FVector2D(1.0f, 0.0f);
    FVector2D randomVec = vecX.GetRotated(randomAngle);

    return center + randomVec * randomRadius;
}

FVector2D FMap2DSampler_PoissonDisk::GenerateRandomPoint_CoordinateBased(float minX, float minY, float maxX, float maxY)
{
    float ranX = FRandomGenerateManager::GetInstance()->RandRange_Float(minX, maxX, ERandomMethodType::Normal);
    float ranY = FRandomGenerateManager::GetInstance()->RandRange_Float(minY, maxY, ERandomMethodType::Normal);

    return FVector2D(ranX, ranY);
}

bool FMap2DSampler_PoissonDisk::IsValidPoint(FVector2D newPoint, float impactRadius) const
{
    if (!m_Region.IsInsideRegion(newPoint, true))
    {
        return false;
    }

    for (int i = 0; i < m_GeneratedNodeSamples.Num(); ++i)
    {
        FVector2D testingPoint = m_GeneratedNodeSamples[i];
        float distance = FVector2D::Distance(testingPoint, newPoint);
        if (distance <= impactRadius)
        {
            return false;
        }
    }

    return true;
}