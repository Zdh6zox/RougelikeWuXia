// Fill out your copyright notice in the Description page of Project Settings.


#include "EventBase.h"
#include "EventChannel.h"

void FEventBase::Broadcast(UEventChannel* channel)
{
	channel->BroadcastEvent(this);
}

void FEventListener::BindFunction(TFunction<void(FEventBase*)> callbackFunc)
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

void FEventListener::ExecuteIfBound(FEventBase* eventBase)
{
	if (m_EventCallback != NULL)
	{
		m_EventCallback(eventBase);
	}
}