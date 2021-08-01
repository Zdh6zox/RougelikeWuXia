// Fill out your copyright notice in the Description page of Project Settings.


#include "MapConstructor.h"
#include "MapData.h"
#include "MapNodeType.h"
#include "MapNodePreset.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"


UMapData* FMapConstructor::ConstructMap(FMapConstructData& constructingData)
{
	UMapData* newMapData = NewObject<UMapData>();
	
	GetConstructUnitsLists();

	return newMapData;
}

void FMapConstructor::GetConstructUnitsLists()
{
	FString singleNodeTablePath = "DataTable'/Game/MainMap/MapNodeDataTable.MapNodeDataTable'";
	m_SingleNodeTable = LoadObject<UDataTable>(NULL, *singleNodeTablePath);
	check(m_SingleNodeTable != NULL);

	FString presetTablePath = "DataTable'/Game/MainMap/MapNodePressetTable.MapNodePressetTable'";
	m_PresetTable = LoadObject<UDataTable>(NULL, *presetTablePath);
	check(m_PresetTable != NULL);

	TArray<FMapNodeClassData*> singleNodesArr;
	m_SingleNodeTable->GetAllRows<FMapNodeClassData>("", singleNodesArr);
	for (FMapNodeClassData* singleNode : singleNodesArr)
	{
		if (singleNode->Rareness == EMapConstructUnitRarenessType::Necessary)
		{
			m_NecessaryUnitsArr.Add(singleNode);
		}
		else if (singleNode->Rareness == EMapConstructUnitRarenessType::Rare)
		{
			m_RareUnitsArr.Add(singleNode);
		}
		else if (singleNode->Rareness == EMapConstructUnitRarenessType::Normal)
		{
			m_NormalUnitsArr.Add(singleNode);
		}
	}

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
}