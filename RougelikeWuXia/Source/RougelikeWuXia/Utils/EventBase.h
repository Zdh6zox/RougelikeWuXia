// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UEventChannel;
class ROUGELIKEWUXIA_API FEventBase
{
public:
	void Broadcast(UEventChannel* channel);
};

template<class T,typename U>
class ROUGELIKEWUXIA_API FEventCallback
{

};

class ROUGELIKEWUXIA_API FEventListener
{
public:
	void JoinChannel(UEventChannel* channelToJoin);
	void LeaveChannel(UEventChannel* channelToLeave);
	void BindFunction(TFunction<void(FEventBase*)> callbackFunc);
	void ExecuteIfBound(FEventBase* eventBase);

private:
	TFunction<void(FEventBase*)> m_EventCallback;
};
