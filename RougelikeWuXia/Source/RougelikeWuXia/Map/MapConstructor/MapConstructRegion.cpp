// Fill out your copyright notice in the Description page of Project Settings.


#include "MapConstructRegion.h"

bool FMapConstructRegion::IsInsideRegion(FVector2D testingLoc)
{
    int32 i;
    int32 j = RegionVertices.Num() - 1;

    bool bOddNodes = false;

    for (i = 0; i < RegionVertices.Num(); ++i)
    {
        if (
            (RegionVertices[i].Y < testingLoc.Y && RegionVertices[j].Y >= testingLoc.Y || RegionVertices[j].Y < testingLoc.Y && RegionVertices[i].Y >= testingLoc.Y) &&
            (RegionVertices[i].X <= testingLoc.X || RegionVertices[j].X <= testingLoc.X)
            )
        {
            if (RegionVertices[i].X + (testingLoc.Y - RegionVertices[i].Y) / (RegionVertices[j].Y - RegionVertices[i].Y) * (RegionVertices[j].X - RegionVertices[i].X) < testingLoc.X)
            {
                bOddNodes = !bOddNodes;
            }
        }
        j = i;
    }

    return bOddNodes;
}
