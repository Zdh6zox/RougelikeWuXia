// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class AActor;
class ROUGELIKEWUXIA_API FObjectPartitionBuckets
{
private:
    static const unsigned long NUM_2D_BUCKETS = 128;
    static const unsigned long NUM_BUCKETS = NUM_2D_BUCKETS * NUM_2D_BUCKETS;
    static const unsigned long NUM_OBJECTS_PER_BUCKETS = 16;
    // partition buckets;
    AActor* m_Buckets[NUM_BUCKETS][NUM_OBJECTS_PER_BUCKETS];
    // buckets counts;
    unsigned long m_ObjectCount[NUM_BUCKETS];

    float  m_BucketSize;
public:
    FObjectPartitionBuckets() : m_BucketSize(200.f) {}
    void Clear()
    {
        for (long i = 0; i < NUM_BUCKETS; i++)
        {
            m_ObjectCount[i] = 0;
        }
    }

    void Build(TArray<AActor*>& objectList);
    void Gather(const TArray<AActor*>& ignoredActors, FVector targetPosition, float radius, TArray<AActor*>& foundObjects);

private:
    void GetUVForPosition(FVector pos, long& u, long& v);
};

class ROUGELIKEWUXIA_API FObjectPartition
{
public:
};
