// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MapNodeType.generated.h"

/**
 * 
*/
class AMapNodeActor;
UENUM(BlueprintType)
enum class EMapNodeClassRarenessEnum : uint8
{
	Necessary,
	Normal,
	Rare
};


USTRUCT(BlueprintType)
struct ROUGELIKEWUXIA_API FMapNodeClassData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		float NodeConstructImpactRadius;

	UPROPERTY(EditAnywhere)
		EMapNodeClassRarenessEnum Rareness;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AMapNodeActor> NodeActorTemplate;
};