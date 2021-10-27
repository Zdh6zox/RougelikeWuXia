// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapConstructData.h"
#include "MapEnums.h"

/**
 * 
 */
class UMapData;
class UDataTable;
class AMainMapActor;
struct FMapPresetImpactRadius;
struct FMapNodePreset;

class ROUGELIKEWUXIA_API FMapConstructor
{
public:
	UMapData* ConstructMap(AMainMapActor* mapActor, FMapConstructData& constructingData);

	struct FMapNodeLocation
	{
	public:
		FMapNodeLocation(EMapConstructUnitRarenessType rareness, const TArray<FMapPresetImpactRadius>& impactRadius, FVector2D location)
		{
			Rareness = rareness;
			ImpactRadiusList = impactRadius;
			location = location;
		}
		TArray<FMapPresetImpactRadius> ImpactRadiusList;
		EMapConstructUnitRarenessType Rareness;
		FVector2D Location;
	};

private:
	void GetConstructUnitsLists();
	FVector2D GeneratePosition(FMapNodePreset* preset);
	bool CheckGeneratedLocationValid(const FMapNodeLocation& checkingLoc);

	void PoissonDiskSamplingGenerate();

	AMainMapActor* m_MapActor = nullptr;
	float m_MapSizeX;
	float m_MapSizeY;
	TArray<FMapNodePreset*> m_NecessaryUnitsArr;
	TArray<FMapNodePreset*> m_RareUnitsArr;
	TArray<FMapNodePreset*> m_NormalUnitsArr;
	TArray<FMapNodeLocation> m_ConstructedLocationArr;
    UDataTable* m_SingleNodeTable;
	UDataTable* m_PresetTable;
};

class FMapConstructPoissonDiskSampler
{
public:
	FMapConstructPoissonDiskSampler(int mainNodeNum, int subNodeNum, float mapSize_X, float mapSize_Y)
		: m_MapSizeX(mapSize_X), m_MapSizeY(mapSize_Y), m_MainNodeNum(mainNodeNum), m_SubNodeNum(subNodeNum)
	{
        m_GeneratedMainNodeSamples.Reserve(mainNodeNum);
        m_GeneratedSubNodeSamples.Reserve(subNodeNum);
        m_ActivedPoint.Reserve(mainNodeNum);
	}

    void RunSampler();
private:
	TArray<FVector2D> m_GeneratedMainNodeSamples;
    TArray<FVector2D> m_GeneratedSubNodeSamples;
	TArray<FVector2D> m_ActivedPoint;
	float m_MapSizeX;
	float m_MapSizeY;
	int m_MainNodeNum;
	int m_SubNodeNum;
};