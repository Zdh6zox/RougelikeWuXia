// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMapActor.h"
#include "MapBlock.h"
#include "MapConstructor/MapConstructor.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

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
	
	m_MapConstructor = new FMapConstructor();

	m_ShowDebug = true;
}

void AMainMapActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	delete m_MapConstructor;
}

void AMainMapActor::TriggerDisplayStep()
{
	m_MapConstructor->ShowDebugStep(this);
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
		GetWorldTimerManager().SetTimer(m_DebugDisplayTimer, this, &AMainMapActor::TriggerDisplayStep, 3.0f, true);

        //GeneratedMainLocs.Empty();
        //m_MapConstructor->GetConstructedMainNodeLocs(GeneratedMainLocs);

        //for (int i = 0; i < GeneratedMainLocs.Num(); ++i)
        //{
        //    FVector generatedLoc = GetActorLocation() + FVector(GeneratedMainLocs[i].X, GeneratedMainLocs[i].Y, 0.0f);
        //    DrawDebugSphere(GetWorld(), generatedLoc, MapConstructData.MainNodeRadius / 4, 8, FColor::Orange, false, 30.f);
        //    //DrawDebugSphere(GetWorld(), generatedLoc, MapConstructData.MainNodeRadius, 16, FColor::Red, false, 30.f);
        //}

        //GeneratedSubLocs.Empty();
        //m_MapConstructor->GetConstructedSubNodeLocs(GeneratedSubLocs);

        //for (int i = 0; i < GeneratedSubLocs.Num(); ++i)
        //{
        //    FVector generatedLoc = GetActorLocation() + FVector(GeneratedSubLocs[i].X, GeneratedSubLocs[i].Y, 0.0f);
        //    DrawDebugSphere(GetWorld(), generatedLoc, MapConstructData.SubNodeRadius / 4, 8, FColor::Green, false, 30.f);
        //    //DrawDebugSphere(GetWorld(), generatedLoc, MapConstructData.SubNodeRadius, 16, FColor::Blue, false, 30.f);
        //}

        //TArray<FVoronoiDiagramGeneratedSite> sites;
        //m_MapConstructor->GetGeneratedSites(sites);

        //for (int i = 0; i < sites.Num(); ++i)
        //{
        //    FVector sitsOrigin = GetActorLocation() + FVector(sites[i].Coordinate.X, sites[i].Coordinate.Y, 0.0f);
        //    DrawDebugSphere(GetWorld(), sitsOrigin, 5.0f, 10.0f, FColor::Black, false, 30.f);

        //    for (int j = 0; j < sites[i].Edges.Num(); ++j)
        //    {
        //        FVoronoiDiagramGeneratedEdge edge = sites[i].Edges[j];
        //        FVector startPos = GetActorLocation() + FVector(edge.LeftEndPoint.X, edge.LeftEndPoint.Y, 0.0f);
        //        FVector endPos = GetActorLocation() + FVector(edge.RightEndPoint.X, edge.RightEndPoint.Y, 0.0f);
        //        DrawDebugLine(GetWorld(), startPos, endPos, FColor::Blue, false, 30.f, (uint8)'\000', 10.f);
        //    }
        //}
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

void AMainMapActor::DebugGenMainCityLocs()
{
	m_MapConstructor->GenerateMainCityLocations(this, MapConstructData);
}

void AMainMapActor::DebugDividRegion()
{
	m_MapConstructor->DividRegion(this,MapConstructData);
}

void AMainMapActor::DebugGenSubNodesLocs()
{
	m_MapConstructor->GenerateSubNodesLocations(this,MapConstructData);
}

void AMainMapActor::DebugGenLinks()
{
	m_MapConstructor->GenerateLinks(this,MapConstructData);
}

void AMainMapActor::DebugSpawnActors()
{

}
#pragma optimize("",on)
