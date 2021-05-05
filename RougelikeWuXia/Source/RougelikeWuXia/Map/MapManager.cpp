// Fill out your copyright notice in the Description page of Project Settings.


#include "MapManager.h"
#include "Managers/GameManager.h"
#include "Map/MapData.h"
#include "SaveableData.h"

void FMapManager::Initialize(AGameManager* gm)
{
	m_GMCache = gm;
}

void FMapManager::SaveCurrentMap(USaveableData* saveableData)
{
	if (saveableData == NULL || m_MapData == NULL)
	{
		return;
	}

	m_MapData->GatherMapStaticData(saveableData->MapData);
}