// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventChannel.generated.h"

/**
 * 
 */
class FEventListener;
class FEventBase;
UCLASS()
class ROUGELIKEWUXIA_API UEventChannel : public UObject
{
	GENERATED_BODY()
public:
	void BroadcastEvent(FEventBase* event);
	void AddListener(TSharedPtr<FEventListener> listener);
	void RemoveListener(TSharedPtr<FEventListener> listener);

private:
	TArray<TWeakPtr<FEventListener>> m_Listeners;
};
