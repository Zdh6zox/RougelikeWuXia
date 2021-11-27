// Fill out your copyright notice in the Description page of Project Settings.


#include "MapConstructor.h"
#include "RougelikeWuXia.h"
#include "Map/MapData.h"
#include "Map/MainMapActor.h"
#include "Managers/GameManager.h"
#include "Map/MapNodeType.h"
#include "Map/MapNodePreset.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
#include "MapConstructorSampler.h"


UMapData* FMapConstructor::ConstructMap(AMainMapActor* mapActor, const FMapConstructData& constructingData)
{
	UMapData* newMapData = NewObject<UMapData>();
	//m_MapActor = mapActor;
	//GetConstructUnitsLists();

	m_Sampler = new FMapConstructPoissonDiskSampler(constructingData.MaxMainNodeCount, constructingData.MainNodeRadius, constructingData.MapSize.X, constructingData.MapSize.Y, 20);
	m_Sampler->RunSampler();

	TArray<FVector2D> constructedMainLoc;
	m_Sampler->GetGeneratedMainNodes(constructedMainLoc);
	m_GeneratedMainNodeLocs.Append(constructedMainLoc);

	delete m_Sampler;

	m_Sampler = new FMapConstructPoissonDiskSampler(constructingData.MaxSubNodeCount, constructedMainLoc, constructingData.MainNodeRadius,
		constructingData.SubNodeRadius, constructingData.MapSize.X, constructingData.MapSize.Y, 20);
	m_Sampler->RunSampler();
	TArray<FVector2D> constructedSubLoc;
	m_Sampler->GetGeneratedSubNodes(constructedSubLoc);
	m_GeneratedSubNodeLocs.Append(constructedSubLoc);

	m_IsFinished = true;
	return newMapData;
}

void FMapConstructor::GetConstructedNodeLoc(TArray<FVector2D>& locs) const
{
	locs.Append(m_GeneratedMainNodeLocs);

	locs.Append(m_GeneratedSubNodeLocs);
}

void FMapConstructor::GetConstructedMainNodeLocs(TArray<FVector2D>& locs) const
{
	locs.Append(m_GeneratedMainNodeLocs);
}

void FMapConstructor::GetConstructedSubNodeLocs(TArray<FVector2D>& locs) const
{
	locs.Append(m_GeneratedSubNodeLocs);
}

void FMapConstructor::GetConstructUnitsLists()
{
	FString presetTablePath = "DataTable'/Game/MainMap/MapNodePressetTable.MapNodePressetTable'";
	m_PresetTable = LoadObject<UDataTable>(NULL, *presetTablePath);
	check(m_PresetTable != NULL);

	TArray<FMapNodePreset*> presetsArr;
	m_PresetTable->GetAllRows<FMapNodePreset>("", presetsArr);
	for (FMapNodePreset* preset : presetsArr)
	{
		if (preset->Rareness == EMapConstructUnitRarenessType::Necessary)
		{
			m_NecessaryUnitsArr.Add(preset);
		}
		else if (preset->Rareness == EMapConstructUnitRarenessType::Rare)
		{
			m_RareUnitsArr.Add(preset);
		}
		else if (preset->Rareness == EMapConstructUnitRarenessType::Normal)
		{
			m_NormalUnitsArr.Add(preset);
		}
	}

	for (FMapNodePreset* preset : m_NecessaryUnitsArr)
	{
		
	}
}

FVector2D FMapConstructor::GeneratePosition(FMapNodePreset* preset)
{
	if (preset->Rareness == EMapConstructUnitRarenessType::Necessary)
	{
		FRandomStream& ranStream = AGameManager::GetGameManager(m_MapActor->GetWorld())->GetRandomStream();
		float loc_X = ranStream.GetFraction()* m_MapSizeX;
		float loc_Y = ranStream.GetFraction()* m_MapSizeY;
		FMapNodeLocation generatedLocVec(EMapConstructUnitRarenessType::Necessary, preset->PresetImpactRadiusList, FVector2D(loc_X, loc_Y));
		if (CheckGeneratedLocationValid(generatedLocVec))
		{
			m_ConstructedLocationArr.Add(generatedLocVec);
			return generatedLocVec.Location;
		}
	}
	else if (preset->Rareness == EMapConstructUnitRarenessType::Rare)
	{
	}
	else if (preset->Rareness == EMapConstructUnitRarenessType::Normal)
	{
	}

	UE_LOG(LogMain, Error, TEXT("Cannot Generate New Location"));

	return FVector2D::ZeroVector;
}

bool FMapConstructor::CheckGeneratedLocationValid(const FMapNodeLocation& checkingLoc)
{
	FVector2D checkingVec2 = checkingLoc.Location;
	for (const FMapNodeLocation& nodeLoc : m_ConstructedLocationArr)
	{
		//check if vec2 inside any impact radius
		float distance = FVector2D::Distance(nodeLoc.Location, checkingVec2);
		for (auto& impactRadius : nodeLoc.ImpactRadiusList)
		{
			if (impactRadius.Rareness == checkingLoc.Rareness)
			{

			}
		}
	}

	return false;
}