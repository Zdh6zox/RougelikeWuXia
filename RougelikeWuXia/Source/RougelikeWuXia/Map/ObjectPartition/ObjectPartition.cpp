// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPartition.h"
#include "Engine/World.h"

void FObjectPartitionBuckets::GetUVForPosition(FVector pos, long& u, long& v)
{
    float x = fmod(pos.X / m_BucketSize, (float)NUM_2D_BUCKETS);
    float y = fmod(pos.Y / m_BucketSize, (float)NUM_2D_BUCKETS);

    u = (long)x;
    v = (long)y;
}

void FObjectPartitionBuckets::Gather(const TArray<AActor*>& ignoredActors, FVector targetPosition, float radius, TArray<AActor*>& foundObjects)
{
    // Radius is in meters, so convert in pixels
    FVector Position = targetPosition;

    float squaredRadius = radius * radius;
    const long scanradius = 1 + (long)(radius / m_BucketSize);

    long u, v;
    GetUVForPosition(Position, u, v);

    long minu = u - scanradius;
    long maxu = u + scanradius;
    long minv = v - scanradius;
    long maxv = v + scanradius;

    long diameter = scanradius * 2;
    if (diameter >= NUM_2D_BUCKETS)
    {
        minu = 0;
        maxu = (long)(NUM_2D_BUCKETS - 1);
    }
    if (diameter >= NUM_2D_BUCKETS)
    {
        minv = 0;
        maxv = (long)(NUM_2D_BUCKETS - 1);
    }

    for (long vv = minv; vv <= maxv; ++vv)
    {
        const long vvoffset = (vv % NUM_2D_BUCKETS) * NUM_2D_BUCKETS;

        for (long uu = minu; uu <= maxu; ++uu)
        {
            const long elemIndex = (uu % NUM_2D_BUCKETS) + vvoffset;
            const long bucketCount = m_ObjectCount[elemIndex];
            for (long cnt = 0; cnt < bucketCount; ++cnt)
            {
                AActor* object = m_Buckets[elemIndex][cnt];
                FVector oPos = object->GetActorLocation();
                float sqdist = (oPos - targetPosition).SizeSquared();
                if (sqdist <= squaredRadius && !ignoredActors.Contains(object))
                {
                    foundObjects.Add(object);
                }
            }
        }
    }
}

void FObjectPartitionBuckets::Build(TArray<AActor*>& objectList)
{
    for (AActor* object : objectList)
    {
        if (object)
        {
            FVector objPos = object->GetActorLocation();
            long u, v;
            GetUVForPosition(objPos, u, v);

            long index = v * NUM_2D_BUCKETS + u;
            long objectCount = m_ObjectCount[index];
            if (objectCount < NUM_OBJECTS_PER_BUCKETS)
            {
                m_ObjectCount[index] ++;
                m_Buckets[index][objectCount] = object;
            }
        }
    }
}