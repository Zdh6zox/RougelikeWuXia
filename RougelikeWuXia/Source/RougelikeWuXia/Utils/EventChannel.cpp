// Fill out your copyright notice in the Description page of Project Settings.


#include "EventChannel.h"
#include "EventBase.h"

void UEventChannel::AddListener(TSharedPtr<FEventListener> listener)
{
	m_Listeners.Add(TWeakPtr<FEventListener>(listener));
}

void UEventChannel::RemoveListener(TSharedPtr<FEventListener> listener)
{
	m_Listeners.Remove(TWeakPtr<FEventListener>(listener));
}

void UEventChannel::BroadcastEvent(UEventBase* event)
{
	//for (auto& listener : m_Listeners)
	//{
	//	if (listener.IsValid())
	//	{
	//		listener.Pin()->ExecuteIfBound(event);
	//	}
	//}
}