// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"
#include "GameManager.h"
#include "GameFramework/Actor.h"
#include "Character/CharacterBase.h"
#include "RougelikeWuXia.h"


void FBattleManager::Initialize(AGameManager* gm)
{
	m_GameManager = gm;
}

void FBattleManager::BeginBattle(const TArray<ACharacterBase*>& characters)
{
	if (GetCurrentBattlePhase() != EBattlePhaseType::NotInBattle)
	{
#ifdef WITH_EDITOR
		UE_LOG(LogMain, Error, TEXT("already in battle"));
#endif // WITH_EDITOR

		return;
	}
#ifdef WITH_EDITOR
	FString battleParticipantsStr;
	for (auto& character : characters)
	{
		battleParticipantsStr += AActor::GetDebugName(character);
		battleParticipantsStr += " ";
	}

	UE_LOG(LogMain, Log, TEXT("%s begin combat"), *battleParticipantsStr);
#endif

	m_CurBattleParticipants.Append(characters);
	SetCurrentBattlePhase(EBattlePhaseType::BattleStart);
	BattleFinishedEvent_OneP.Broadcast(characters);
}

void FBattleManager::SetCurrentBattlePhase(EBattlePhaseType curBattlePhase)
{
	if (m_CurBattlePhase == curBattlePhase)
	{
		return;
	}

#ifdef WITH_EDITOR
	FString phaseStr;
	switch (curBattlePhase)
	{
	case EBattlePhaseType::NotInBattle:
		phaseStr = "Not In Battle";
	case EBattlePhaseType::BattleStart:
		phaseStr = "Battle Start";
		break;
	case EBattlePhaseType::MainPhase:
		phaseStr = "Main Phase";
		break;
	case EBattlePhaseType::Settlement:
		phaseStr = "Battle Settlement";
		break;
	default:
		break;
	}
#endif // WITH_EDITOR

	m_CurBattlePhase = curBattlePhase;
}

void FBattleManager::SetCurrentRoundPhase(ERoundPhaseType curRoundPhase)
{
	if (m_CurRoundPhase == curRoundPhase)
	{
		return;
	}

#ifdef WITH_EDITOR
	FString phaseStr;
	switch (curRoundPhase)
	{
	case ERoundPhaseType::RoundStart:
		phaseStr = "Round Start";
		break;
	case ERoundPhaseType::PreparePhase:
		phaseStr = "Prepare Phase";
		break;
	case ERoundPhaseType::ParticipantTurnStart:
		phaseStr = "Participant Turn Start";
		break;
	case ERoundPhaseType::ParticipantTurnExecute:
		phaseStr = "Participant Turn Execute";
		break;
	case ERoundPhaseType::ParticipantTurnEnd:
		phaseStr = "Participant Turn End";
		break;
	case ERoundPhaseType::RoundEnd:
		phaseStr = "Round End";
		break;
	default:
		break;
	}
	UE_LOG(LogMain, Log, TEXT("Enter Phase : %s"), *phaseStr);
#endif
	m_CurRoundPhase = curRoundPhase;
}

void FBattleManager::EndBattle()
{
	if (GetCurrentBattlePhase() == EBattlePhaseType::NotInBattle)
	{
#ifdef WITH_EDITOR
		UE_LOG(LogMain, Error, TEXT("already exit battle"));
#endif // WITH_EDITOR

		return;
	}
#ifdef WITH_EDITOR
	UE_LOG(LogMain, Log, TEXT("end combat"));
#endif

	SetCurrentBattlePhase(EBattlePhaseType::NotInBattle);
	BattleFinishedEvent_OneP.Broadcast(m_CurBattleParticipants);
	m_CurBattleParticipants.Empty();
}

void FBattleManager::ParticipantBeginTurn(ACharacterBase* turnOwner)
{
#ifdef WITH_EDITOR
	UE_LOG(LogMain, Log, TEXT("Character %s begin turn"), *AActor::GetDebugName(turnOwner));
#endif
}

void FBattleManager::ParticipantEndTurn(ACharacterBase* turnOwner)
{
#ifdef WITH_EDITOR
	UE_LOG(LogMain, Log, TEXT("Character %s end turn"), *AActor::GetDebugName(turnOwner));
#endif
}

void FBattleManager::UpdateBattle()
{
	switch (m_CurBattlePhase)
	{
	case EBattlePhaseType::NotInBattle:
		break;
	case EBattlePhaseType::BattleStart:
		//Do battle start stuff

		SetCurrentBattlePhase(EBattlePhaseType::MainPhase);
		SetCurrentRoundPhase(ERoundPhaseType::RoundStart);
		break;
	case EBattlePhaseType::MainPhase:
		UpdateRound();
		break;
	case EBattlePhaseType::Settlement:
		//Do Settlement stuff
		SetCurrentBattlePhase(EBattlePhaseType::NotInBattle);
		break;
	default:
		break;
	}
}

void FBattleManager::UpdateRound()
{
	switch (m_CurRoundPhase)
	{
	case ERoundPhaseType::RoundStart:
		break;
	case ERoundPhaseType::PreparePhase:
		break;
	case ERoundPhaseType::ParticipantTurnStart:
		break;
	case ERoundPhaseType::ParticipantTurnExecute:
		break;
	case ERoundPhaseType::ParticipantTurnEnd:
		break;
	case ERoundPhaseType::RoundEnd:
		break;
	default:
		break;
	}
}