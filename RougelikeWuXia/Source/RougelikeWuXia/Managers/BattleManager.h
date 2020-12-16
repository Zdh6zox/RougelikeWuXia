// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattlePhaseEnum.h"


class AGameManager;
class ACharacterBase;
class APlayerCharacter;
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
	FTurnEndEvent_OneParam TurnEndEvent_OneP;

	FPlayerSetupPhaseStartEvent_NoParam PlayerSetupPhaseStartEvent_NoP;
	FPlayerSetupPhaseEndEvent_NoParam PlayerSetupPhaseEndEvent_NoP;

	void BeginBattle(const TArray<ACharacterBase*>& characters);
	void EndBattle();
	void ParticipantBeginTurn(ACharacterBase* turnOwner);
	void ParticipantEndTurn(ACharacterBase* turnOwner);

	void EnterSolo(ACharacterBase* enemy);
	void ExitSolo();

	void EnterPlayerPhase();
	void ExitPlayerPhase();

	void UpdateBattle();
	void UpdateRound();

	bool CheckIfBattleFinished() const;

	inline ERoundPhaseType GetCurrentRoundPhase() const { return m_CurRoundPhase; }
	void SetCurrentRoundPhase(ERoundPhaseType curRoundPhase);

	inline EBattlePhaseType GetCurrentBattlePhase() const { return m_CurBattlePhase; }
	void SetCurrentBattlePhase(EBattlePhaseType curBattlePhase);

	void OnParticipantDead(ACharacterBase* participant);
	void OnTurnEnd(ACharacterBase* turnOwner);

	void RegisterBattleEvent(ACharacterBase* character);
	void UnregisterBattleEvent(ACharacterBase* character);

	inline const TArray<ACharacterBase*>& GetRoundExecutionOrder() { return m_CurRoundOrderSorted; }

private:
	void SortRoundOrder(const TArray<ACharacterBase*>& participants);
	bool PopNextTurnOwner();

	ERoundPhaseType m_CurRoundPhase;
	EBattlePhaseType m_CurBattlePhase;
	int m_CurrentRoundNum;
	ACharacterBase* m_CurTurnOwner;
	APlayerCharacter* m_PlayerCharacter;
	
	TArray<ACharacterBase*> m_CurBattleParticipants;
	TArray<ACharacterBase*> m_CurRoundOrderSorted;
private:
	AGameManager* m_GameManager;
};
