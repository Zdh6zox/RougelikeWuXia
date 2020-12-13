// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"
#include "GameManager.h"
#include "GameFramework/Actor.h"
#include "Character/CharacterBase.h"
#include "Character/PlayerCharacter.h"
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
	for (auto& character : characters)
	{
		character->CharacterDeadEvent_OneP.AddSP(this, &FBattleManager::OnParticipantDead);
		if (character->IsA<APlayerCharacter>())
		{
			m_PlayerCharacter = Cast<APlayerCharacter>(character);
		}
	}

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
		break;
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
	case ERoundPhaseType::PlayerPreparePhase:
		phaseStr = "Player Prepare Phase";
		break;
	case ERoundPhaseType::PlayerAttackPhase:
		phaseStr = "Player Attack Phase";
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

	TurnBeginEvent_OneP.Broadcast(turnOwner);
}

void FBattleManager::ParticipantEndTurn(ACharacterBase* turnOwner)
{
#ifdef WITH_EDITOR
	UE_LOG(LogMain, Log, TEXT("Character %s end turn"), *AActor::GetDebugName(turnOwner));
#endif

	TurnEndEvent_OneP.Broadcast(turnOwner);
}

void FBattleManager::SortRoundOrder(const TArray<ACharacterBase *>& participants)
{
	//sort to produce round order

	//Temp
	for (auto& participant : participants)
	{
		if (participant->CheckIsAlive())
		{
			m_CurRoundOrderSorted.Add(participant);
		}
	}
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
		m_CurrentRoundNum = 0;
		SetCurrentRoundPhase(ERoundPhaseType::RoundStart);
		break;
	case EBattlePhaseType::MainPhase:
		if (!CheckIfBattleFinished())
		{
			UpdateRound();
		}
		else
		{
			SetCurrentBattlePhase(EBattlePhaseType::Settlement);
		}
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
	{
		m_CurrentRoundNum++;
		RoundStartedEvent_OneP.Broadcast(m_CurrentRoundNum);
		SortRoundOrder(m_CurBattleParticipants);

		if (PopNextTurnOwner())
		{
			SetCurrentRoundPhase(ERoundPhaseType::ParticipantTurnStart);
		}
		else
		{
			SetCurrentRoundPhase(ERoundPhaseType::RoundEnd);
		}
		break;
	}
	case ERoundPhaseType::PlayerPreparePhase:
		break;
	case ERoundPhaseType::PlayerAttackPhase:
		break;
	case ERoundPhaseType::ParticipantTurnStart:
		ParticipantBeginTurn(m_CurTurnOwner);
		SetCurrentRoundPhase(ERoundPhaseType::ParticipantTurnExecute);
		break;
	case ERoundPhaseType::ParticipantTurnExecute:
		if (m_CurTurnOwner->IsA<APlayerCharacter>())
		{
			EnterPlayerPhase();
		}
		break;
	case ERoundPhaseType::ParticipantTurnEnd:
	{
		ParticipantEndTurn(m_CurTurnOwner);
		if (PopNextTurnOwner())
		{
			SetCurrentRoundPhase(ERoundPhaseType::ParticipantTurnStart);
		}
		else
		{
			SetCurrentRoundPhase(ERoundPhaseType::RoundEnd);
		}
		break;
	}
	case ERoundPhaseType::RoundEnd:
		RoundFinishedEvent_OneP.Broadcast(m_CurrentRoundNum);
		break;
	default:
		break;
	}
}

bool FBattleManager::CheckIfBattleFinished() const
{
	//Check if enemy all dead
	bool hasEnemy = false;
	for (auto& character : m_CurBattleParticipants)
	{
		if (character->IsEnemy )
		{
			if (character->CheckIsAlive())
			{
				hasEnemy = true;
				break;
			}
		}
	}

	//Check if player is dead
	bool isPlayerDead = m_PlayerCharacter->CheckIsAlive();

	return !(hasEnemy && !isPlayerDead);
}

bool FBattleManager::PopNextTurnOwner()
{
	if (m_CurRoundOrderSorted.Num() > 0)
	{
		m_CurTurnOwner = m_CurRoundOrderSorted.Pop(true);
		return true;
	}

	return false;
}

void FBattleManager::OnParticipantDead(ACharacterBase* participant)
{
	m_CurRoundOrderSorted.Remove(participant);
}

void FBattleManager::OnTurnEnd(ACharacterBase* turnOwner)
{
	SetCurrentRoundPhase(ERoundPhaseType::ParticipantTurnEnd);
}

void FBattleManager::EnterPlayerPhase()
{
	SetCurrentRoundPhase(ERoundPhaseType::PlayerPreparePhase);
}

void FBattleManager::ExitPlayerPhase()
{
	SetCurrentRoundPhase(ERoundPhaseType::ParticipantTurnEnd);
}

void FBattleManager::EnterSolo(ACharacterBase* enemy)
{
	if (m_CurBattlePhase != EBattlePhaseType::MainPhase || m_CurRoundPhase != ERoundPhaseType::PlayerPreparePhase)
	{
		return;
	}

	SetCurrentRoundPhase(ERoundPhaseType::PlayerAttackPhase);
}

void FBattleManager::ExitSolo()
{
	SetCurrentRoundPhase(ERoundPhaseType::PlayerPreparePhase);
}