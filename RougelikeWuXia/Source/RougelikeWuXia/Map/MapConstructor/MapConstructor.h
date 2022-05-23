// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapConstructData.h"
#include "Map/MapEnums.h"
#include "Map/MapNodePreset.h"
#include "MapConstructRegion.h"
#include "Division/MapConstructorRegionDivision.h"

/**
 * 
 */
class UMapData;
class UDataTable;
class AMainMapActor;
class FMapConstructorSampler;
class FMapConstructorRegionDivision;
class FMapConstructDebugger;
class FVoronoiDiagramGeneratedSite;
class UWorld;

//先生成区域地图：
//在维诺图生成后，使用泊松盘生成
//后生成门派，奇遇点

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
	~FMapConstructor();

	enum MapConstructPhase
	{
		NotStarted,
		MainLocsGenerated,
		RegionDivided,
		SubLocsGenerated,
		LinksGenerated
	};

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
	void GetGeneratedRegions(TArray<class FMapConstructRegion>& regions) const;
	bool IsFinished() const { return m_IsFinished; }

    void ShowDebugStep(AMainMapActor* mapActor);

	void GenerateMainCityLocations(AMainMapActor* mapActor, const FMapConstructData& constructingData);
	void DividRegion(AMainMapActor* mapActor, const FMapConstructData& constructingData);
	void GenerateSubNodesLocations(AMainMapActor* mapActor, const FMapConstructData& constructingData);
	void GenerateLinks(AMainMapActor* mapActor, const FMapConstructData& constructingData);

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
    TArray<class FMapConstructRegion> m_Regions;
	//TArray<class FVoronoiDiagramGeneratedSite> m_Sites;

	TArray<FMapConstructDebugger*> m_Debuggers;
	int m_CurDisplayStep = 0;
	MapConstructPhase m_CurPhase = MapConstructPhase::NotStarted;
};

