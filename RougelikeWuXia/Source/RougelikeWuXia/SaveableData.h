// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Map/MapData.h"
#include "SaveableData.generated.h"

class UPlayerRuntimeData;
/**
 * 
 */
UCLASS()
class ROUGELIKEWUXIA_API USaveableData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		UPlayerRuntimeData* PlayerData;

	UPROPERTY()
		FMapDataStatic MapData;
};
