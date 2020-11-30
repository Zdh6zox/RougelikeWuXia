// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Delegates/IDelegateInstance.h"

//Declare Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FRoundFinishedEvent_OneParam, int);
/**
 * 
 */
class AGameManager;
class ROUGELIKEWUXIA_API FBattleManager
{
public:
	void Initialize(AGameManager* gm);
	FRoundFinishedEvent_OneParam RoundFinishedEvent_OneP;

private:
	AGameManager* m_GameManager;
};
