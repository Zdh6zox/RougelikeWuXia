// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGeneratorTestActor.h"
#include "Map2DGenerationResult.h"

// Sets default values
AMapGeneratorTestActor::AMapGeneratorTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void AMapGeneratorTestActor::DebugGenerate2DMap()
{
	FMap2DGenerationResult result;
	FMapGeneratorFacade::Generate2DMapPOIAndLinks(Map2DGenerationSetting, result);

	Display2DMapGenerationResult(&result);
}

void AMapGeneratorTestActor::Display2DMapGenerationResult(FMap2DGenerationResult* result)
{
	for (const FMap2DRegion& region : result->GeneratedRegions)
	{
		FVector actorLocation = GetActorLocation();
		region.DebugDisplayRegion(GetWorld(), FVector2D(actorLocation), SiteDisplayRadius, FColor::MakeRandomColor(), EdgeDisplayColor);
	}
}
