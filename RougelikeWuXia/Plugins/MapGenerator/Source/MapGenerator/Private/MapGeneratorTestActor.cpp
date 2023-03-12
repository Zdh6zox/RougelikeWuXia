// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGeneratorTestActor.h"
#include "Map2DGenerationResult.h"
#include "DrawDebugHelpers.h"
#include "Debug/MapGenerationDebugger.h"

// Sets default values
AMapGeneratorTestActor::AMapGeneratorTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CacheResult = new FMap2DGenerationResult();
	m_Debugger = new FMapGenerationDebugger();
	m_Debugger->SetDebugOwner(this);
}

AMapGeneratorTestActor::~AMapGeneratorTestActor()
{
	delete m_CacheResult;
	delete m_Debugger;
}

// Called when the game starts or when spawned
void AMapGeneratorTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMapGeneratorTestActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AMapGeneratorTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGeneratorTestActor::DebugGenerate2DMap(int& regionNum)
{
	FMap2DGenerationResult result;
	FMapGeneratorFacade::Generate2DMapPOIAndLinks(Map2DGenerationSetting, *m_CacheResult, m_Debugger);

	regionNum = m_CacheResult->GeneratedRegions.Num();
}

void AMapGeneratorTestActor::Display2DMapGenerationResult(int regionIndex)
{
	//Clean previous debug drawing
	FlushPersistentDebugLines(GetWorld());
	FlushDebugStrings(GetWorld());

	if (regionIndex >= m_CacheResult->GeneratedRegions.Num())
	{
		return;
	}

	m_CacheResult->GeneratedRegions[regionIndex].DebugDisplayRegion(GetWorld(), FVector2D(GetActorLocation()), SiteDisplayRadius, SiteDisplayColor, EdgeDisplayColor);
}

int AMapGeneratorTestActor::GetRegionSize() const
{
	if (m_CacheResult == nullptr)
		return 0;

	return m_CacheResult->GeneratedRegions.Num();
}

int AMapGeneratorTestActor::GetDebugPeriodCount() const
{
	return m_Debugger->GetPeriodSize();
}

int AMapGeneratorTestActor::GetDebugPeriodElementCount(int periodInx) const
{
	return m_Debugger->GetPeriodElementSize(periodInx);
}

void AMapGeneratorTestActor::ClearDebugLog()
{
	m_Debugger->ClearDebugLogs();
}

void AMapGeneratorTestActor::ShowDebug(int periodInx, int elementInx) const
{
	m_Debugger->DebugDisplayElement(GetWorld(), periodInx, elementInx);
}