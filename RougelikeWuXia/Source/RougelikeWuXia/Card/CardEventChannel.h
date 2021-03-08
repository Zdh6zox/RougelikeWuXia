// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/EventChannel.h"
#include "CardEventChannel.generated.h"

/**
 * 
 */
UCLASS()
class ROUGELIKEWUXIA_API UCardEventChannel : public UEventChannel
{
	GENERATED_BODY()
	
public:
	static UCardEventChannel* GetChannel()
	{
		if (m_ChannelInstance == NULL)
		{
			m_ChannelInstance = NewObject<UCardEventChannel>();
		}
		return m_ChannelInstance;
	}

private:
	static UCardEventChannel* m_ChannelInstance;
};
