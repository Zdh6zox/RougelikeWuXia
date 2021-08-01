// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapConstructData.h"

/**
 * 
 */
class UMapData;
class UDataTable;

class ROUGELIKEWUXIA_API FMapConstructor
{
public:
	UMapData* ConstructMap(FMapConstructData& constructingData);

private:
	void GetConstructUnitsLists();

	TArray<FTableRowBase*> m_NecessaryUnitsArr;
	TArray<FTableRowBase*> m_RareUnitsArr;
	TArray<FTableRowBase*> m_NormalUnitsArr;
    UDataTable* m_SingleNodeTable;
	UDataTable* m_PresetTable;
};
