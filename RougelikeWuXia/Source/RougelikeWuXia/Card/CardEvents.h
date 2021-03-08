// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/EventBase.h"

class ACardActor;
class ACharacterBase;
/**
 * 
 */
class FCardAboutToTriggerEvent : public FEventBase
{
public:
	ACardActor* TriggeringCard;
	ACharacterBase* TriggeringCharacter;
};

class FCardTriggeredEvent : public FEventBase
{
public:
	ACardActor* TriggeredCard;
};