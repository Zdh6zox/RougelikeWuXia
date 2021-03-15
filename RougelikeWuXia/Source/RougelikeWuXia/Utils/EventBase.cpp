// Fill out your copyright notice in the Description page of Project Settings.


#include "EventBase.h"
#include "EventChannel.h"

void UEventBase::Broadcast(UEventChannel* channel)
{
	channel->BroadcastEvent(this);
}