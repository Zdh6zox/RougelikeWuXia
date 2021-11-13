// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapConstructData.h"
#include "Map/MapEnums.h"

/**
 * 
 */
class UMapData;
class UDataTable;
class AMainMapActor;
struct FMapPresetImpactRadius;
struct FMapNodePreset;
class FMapConstructorSampler;

enum ROUGELIKEWUXIA_API EMapConstructorSampleMethodType
{
	PossionDisk,
	BestCandidate,
	Random
};

class ROUGELIKEWUXIA_API FMapConstructor
{
public:
	UMapData* ConstructMap(AMainMapActor* mapActor, const FMapConstructData& constructingData);

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

	void GetConstructedNodeLoc(TArray<FVector2D>& locs) const;
	bool IsFinished() const { return m_IsFinished; }

private:
	void GetConstructUnitsLists();
	FVector2D GeneratePosition(FMapNodePreset* preset);
	bool CheckGeneratedLocationValid(const FMapNodeLocation& checkingLoc);

	AMainMapActor* m_MapActor = nullptr;
	float m_MapSizeX;
	float m_MapSizeY;
	TArray<FMapNodePreset*> m_NecessaryUnitsArr;
	TArray<FMapNodePreset*> m_RareUnitsArr;
	TArray<FMapNodePreset*> m_NormalUnitsArr;
	TArray<FMapNodeLocation> m_ConstructedLocationArr;
    UDataTable* m_SingleNodeTable;
	UDataTable* m_PresetTable;
	bool m_IsFinished = false;

	FMapConstructorSampler* m_Sampler = nullptr;
};

