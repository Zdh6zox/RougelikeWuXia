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

void FBattleManager::BeginBattle(const TArray<ACharacterBase *> characters)
{
#ifdef WITH_EDITOR
	FString battleParticipantsStr;
	for (auto& character : characters)
	{
		battleParticipantsStr += AActor::GetDebugName(character);
		battleParticipantsStr += " ";
	}

	UE_LOG(LogMain, Log, TEXT("%s begin combat"), *battleParticipantsStr);
#endif
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
#ifdef WITH_EDITOR
	UE_LOG(LogMain, Log, TEXT("End combat"));
#endif
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
	
}