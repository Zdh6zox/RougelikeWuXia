// Fill out your copyright notice in the Description page of Project Settings.


#include "MapConstructor.h"
#include "MapData.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"


UMapData* FMapConstructor::ConstructMap(FMapConstructData& constructingData)
{
	UMapData* newMapData = NewObject<UMapData>();
	return newMapData;
}