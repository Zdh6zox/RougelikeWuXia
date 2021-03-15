// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventListener.generated.h"

/**
 * 
 */
UCLASS()
class ROUGELIKEWUXIA_API UEventListener : public UObject
{
	GENERATED_BODY()
	
public:
    void ConnectHandler(IEventHandler* handler);
    void DisconnectHandler(IEventHandler* handler);
    void JoinChannel(UEventChannel* channelToJoin);
    void LeaveChannel(UEventChannel* channelToLeave);
    void ExecuteIfBound(UEventBase* eventBase);
    void HandleEvent(UEventBase* eventBase);
};

class ROUGELIKEWUXIA_API FEventListener
{
public:
    void JoinChannel(UEventChannel* channelToJoin);
    void LeaveChannel(UEventChannel* channelToLeave);
    void BindFunction(TFunction<void(UEventBase*)> callbackFunc);
    void ExecuteIfBound(UEventBase* eventBase);
    void HandleEvent(UEventBase* eventBase);

private:
    TFunction<void(UEventBase*)> m_EventCallback;

    TArray<IEventHandler*> m_HandlerList;
};
