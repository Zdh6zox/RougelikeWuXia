// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/EventHandler.h"
#include "UObject/NoExportTypes.h"
#include "EventBase.generated.h"
/**
 * 
 */
class UEventChannel;
UCLASS()
class ROUGELIKEWUXIA_API UEventBase : public UObject
{
    GENERATED_BODY()
public:
	void Broadcast(UEventChannel* channel);
};
