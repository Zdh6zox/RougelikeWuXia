// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMapActor.h"
#include "MapBlock.h"
#include "MapConstructor/MapConstructor.h"
#include "MapConstructor/MapConstructorSampler.h"
#include "DrawDebugHelpers.h"

#pragma optimize("",off)
// Sets default values
AMainMapActor::AMainMapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainMapActor::BeginPlay()
{
	Super::BeginPlay();
	
	//Test PossionDiskSampling
	m_MapConstructor = new FMapConstructor();

	ConstructMap();

	m_ShowDebug = true;
}

void AMainMapActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	delete m_MapConstructor;
}

// Called every frame
void AMainMapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (!ConstructCompleted)
	//{
	//	ConstructMap();
	//}

	if (m_MapConstructor->IsFinished()
		&& m_ShowDebug)
	{
		m_ShowDebug = false;
        TArray<FVector2D> locs;
        m_MapConstructor->GetConstructedNodeLoc(locs);

		DrawDebugString(GetWorld(), GetActorLocation(), FString::Printf(TEXT("%d"), locs.Num()), this, FColor::Black, 30.0f);
        for (int i = 0; i < locs.Num(); ++i)
        {
            FVector generatedLoc = GetActorLocation() + FVector(locs[i].X, locs[i].Y, 0.0f);
            DrawDebugSphere(GetWorld(), generatedLoc, 20.f, 4, FColor::Red, true);
            DrawDebugSphere(GetWorld(), generatedLoc, 60.f, 4, FColor::Blue, true);
        }
	}
}

void AMainMapActor::ConstructMap()
{
	//MapData = m_MapConstructor.ConstructMap(MapConstructData);

	//Create Async Task to construct map
	auto task = new FAutoDeleteAsyncTask<FMapConstructAsyncTask>(this);
	if (task)
	{
		task->StartBackgroundTask();
	}
}

void AMainMapActor::ConstructMap_Actual()
{
	////fill main map with blocks according to parameters
	//if (BlockClass == NULL)
	//{
	//	UE_LOG(LogMain, Error, TEXT("Block Class didn't setup on MainMapActor"));
	//	return;
	//}

	//for (int i = 0; i < BlockConstructOneFrame; ++i)
	//{
	//	if (m_CurRow >= MapConstructData.MapSize.X 
	//		&& m_CurColumn >= MapConstructData.MapSize.Y)
	//	{
	//		ConstructCompleted = true;
	//		return;
	//	}

	//	AMapBlock* spawnedBlock = GetWorld()->SpawnActor<AMapBlock>(BlockClass, GetTransform());

	//	if (m_CurRow <= MapConstructData.MapSize.X)
	//	{
	//		if (m_CurColumn < MapConstructData.MapSize.Y)
	//		{
	//			//add offset
	//			FVector2D blockSize = spawnedBlock->BlockSize;
	//			FVector offset = FVector(blockSize.X * m_CurRow, blockSize.Y * m_CurColumn, 0);
	//			spawnedBlock->AddActorWorldOffset(offset, true);

	//			m_CurColumn++;
	//		}

	//		if (m_CurColumn >= MapConstructData.MapSize.Y)
	//		{
	//			if (m_CurRow < MapConstructData.MapSize.X)
	//			{
	//				m_CurRow++;
	//				m_CurColumn = 0;
	//			}
	//			else
	//			{
	//				ConstructCompleted = true;
	//				return;
	//			}
	//		}
	//	}

	//}
	m_MapConstructor->ConstructMap(this, MapConstructData);
	
}

void AMainMapActor::LoadConstructedMap()
{

}
#pragma optimize("",on)
