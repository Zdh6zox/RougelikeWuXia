// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGeneratorTestActor.h"
#include "Map2DGenerationResult.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMapGeneratorTestActor::AMapGeneratorTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CacheResult = new FMap2DGenerationResult();
}

AMapGeneratorTestActor::~AMapGeneratorTestActor()
{
	delete m_CacheResult;
}

// Called when the game starts or when spawned
void AMapGeneratorTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapGeneratorTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGeneratorTestActor::DebugGenerate2DMap(int& regionNum)
{
	FMap2DGenerationResult result;
	FMapGeneratorFacade::Generate2DMapPOIAndLinks(Map2DGenerationSetting, *m_CacheResult);

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