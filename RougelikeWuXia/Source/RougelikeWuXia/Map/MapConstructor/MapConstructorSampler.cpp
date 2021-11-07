// Fill out your copyright notice in the Description page of Project Settings.


#include "MapConstructorSampler.h"
FVector2D FMapConstructPoissonDiskSampler::GenerateRandomPoint(FVector2D center)
{
    //find a random point inside circle ring which inner radius r outer radius 2r
    float randomAngle = FMath::RandRange(0.0f, 2 * PI);
    float randomRadius = FMath::RandRange(m_NodeImpactRadius, 2 * m_NodeImpactRadius);

    FVector2D rotatingVec = FVector2D(1.0f, 0.0f);
    FVector2D randomVec = rotatingVec.GetRotated(randomAngle);

    return center + randomVec * randomRadius;
}

void FMapConstructPoissonDiskSampler::RunSampler_Internal()
{
    //generate first activated point if empty
    if (m_ActivedPoint.Num() == 0)
    {
        float ranX = FMath::RandRange(0.0, m_MapSizeX);
        float ranY = FMath::RandRange(0.0, m_MapSizeY);
        m_GeneratedMainNodeSamples.Add(FVector2D(ranX, ranY));
        m_ActivedPoint.Add(FVector2D(ranX, ranY));
    }


}

void FMapConstructorBestCandidateSampler::RunSampler_Internal()
{

}

void FMapConstructorRandomSampler::RunSampler_Internal()
{

}