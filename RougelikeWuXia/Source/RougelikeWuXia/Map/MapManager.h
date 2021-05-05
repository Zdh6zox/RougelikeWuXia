// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class AGameManager;
class USaveableData;
class UMapData;

class ROUGELIKEWUXIA_API FMapManager
{
public:
	void Initialize(AGameManager* gm);
	void SaveCurrentMap(USaveableData* saveableData);

private:
	AGameManager* m_GMCache;
	UMapData* m_MapData;
};
