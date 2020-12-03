// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Delegates/IDelegateInstance.h"

//Declare Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FRoundFinishedEvent_OneParam, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FTurnBeginEvent_OneParam, ACharacterBase*);
DECLARE_MULTICAST_DELEGATE_OneParam(FTurnEndEvent_OneParam, ACharacterBase*);
/**
 * 
 */
class AGameManager;
class ROUGELIKEWUXIA_API FBattleManager
{
public:
	void Initialize(AGameManager* gm);
	FRoundFinishedEvent_OneParam RoundFinishedEvent_OneP;
	FTurnBeginEvent_OneParam TurnBeginEvent_OneP;
	FTurnBeginEvent_OneParam TurnEndEvent_OneP;

	void BeginBattle(const TArray<ACharacterBase*> characters);
	void EndBattle();
	void ParticipantBeginTurn(ACharacterBase* turnOwner);
	void ParticipantEndTurn(ACharacterBase* turnOwner);

	void UpdateBattle();

private:
	int m_CurrentRoundNum;
	ACharacterBase* m_CurTurnOwner;
	AGameManager* m_GameManager;
};
