// Fill out your copyright notice in the Description page of Project Settings.


#include "EventListener.h"
#include "Utils/EventBase.h"
#include "Utils/EventChannel.h"

void FEventListener::BindFunction(TFunction<void(UEventBase*)> callbackFunc)
{
	m_EventCallback = callbackFunc;
}

void FEventListener::JoinChannel(UEventChannel* channelToJoin)
{
	channelToJoin->AddListener(MakeShareable(this));
}

void FEventListener::LeaveChannel(UEventChannel* channelToLeave)
{
	channelToLeave->RemoveListener(MakeShareable(this));
}

void FEventListener::ExecuteIfBound(UEventBase* eventBase)
{
	if (m_EventCallback != NULL)
	{
		m_EventCallback(eventBase);
	}
}

void FEventListener::HandleEvent(UEventBase* eventBase)
{

}