// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapConstructData.h"
#include "Map/MapEnums.h"
#include "Map/MapNodePreset.h"
#include "MapConstructRegion.h"

/**
 * 
 */
class UMapData;
class UDataTable;
class AMainMapActor;
class FMapConstructorSampler;
class FMapConstructorRegionDivision;
class UWorld;

//TODO: Use Voronoi Diagram to divide region, use generated region as a condition to generate nodes 

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
	void GetConstructedMainNodeLocs(TArray<FVector2D>& locs) const;
	void GetConstructedSubNodeLocs(TArray<FVector2D>& locs) const;
    void GetGeneratedSites(TArray<class FVoronoiDiagramGeneratedSite>& sites) const;
	void GetGeneratedRegions(TArray<class FMapConstructRegion>& regions) const;
	bool IsFinished() const { return m_IsFinished; }

    void ShowDebug(AMainMapActor* mapActor);

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
	TArray<FVector2D> m_GeneratedMainNodeLocs;
	TArray<FVector2D> m_GeneratedSubNodeLocs;
    TArray<FMapConstructRegion> m_Regions;
	TArray<FVoronoiDiagramGeneratedSite> m_Sites;
};

