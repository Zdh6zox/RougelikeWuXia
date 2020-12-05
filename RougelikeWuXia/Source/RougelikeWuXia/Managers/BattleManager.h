// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattlePhaseEnum.h"


class AGameManager;
class ACharacterBase;
//Declare Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FBattleStartEvent_OneParam, const TArray<ACharacterBase*>); //param: involved characters
DECLARE_MULTICAST_DELEGATE_OneParam(FBattleFinishedEvent_OneParam, const TArray<ACharacterBase*>); //param: alive characters, can used for end battle settlement
DECLARE_MULTICAST_DELEGATE_OneParam(FRoundStartEvent_OneParam, int); //param: started round number
DECLARE_MULTICAST_DELEGATE_OneParam(FRoundFinishedEvent_OneParam, int); //param: finished round number
DECLARE_MULTICAST_DELEGATE_OneParam(FTurnBeginEvent_OneParam, ACharacterBase*); // param: started turn owner
DECLARE_MULTICAST_DELEGATE_OneParam(FTurnEndEvent_OneParam, ACharacterBase*);// param: ended turn owner

DECLARE_MULTICAST_DELEGATE(FPlayerSetupPhaseStartEvent_NoParam);
DECLARE_MULTICAST_DELEGATE(FPlayerSetupPhaseEndEvent_NoParam);
/**
 * 
 */
class ROUGELIKEWUXIA_API FBattleManager
{
public:
	void Initialize(AGameManager* gm);

	FBattleStartEvent_OneParam BattleStartedEvent_OneP;
	FBattleFinishedEvent_OneParam BattleFinishedEvent_OneP;
	FRoundStartEvent_OneParam RoundStartedEvent_OneP;
	FRoundFinishedEvent_OneParam RoundFinishedEvent_OneP;
	FTurnBeginEvent_OneParam TurnBeginEvent_OneP;
	FTurnBeginEvent_OneParam TurnEndEvent_OneP;

	FPlayerSetupPhaseStartEvent_NoParam PlayerSetupPhaseStartEvent_NoP;
	FPlayerSetupPhaseEndEvent_NoParam PlayerSetupPhaseEndEvent_NoP;

	void BeginBattle(const TArray<ACharacterBase*> characters);
	void EndBattle();
	void ParticipantBeginTurn(ACharacterBase* turnOwner);
	void ParticipantEndTurn(ACharacterBase* turnOwner);

	void UpdateBattle();

	inline ERoundPhaseType GetCurrentRoundPhase() const { return m_CurRoundPhase; }
private:
	ERoundPhaseType m_CurRoundPhase;
	int m_CurrentRoundNum;
	ACharacterBase* m_CurTurnOwner;
	AGameManager* m_GameManager;
};
