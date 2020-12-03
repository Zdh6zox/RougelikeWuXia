// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"
#include "GameManager.h"
#include "GameFramework/Actor.h"
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
		battleParticipantsStr += TEXT("%s ", *AActor::GetDebugName(character));
	}

	UE_LOG(LogMain, Log, TEXT("%s begin combat", battleParticipantsStr));
#endif
}

void FBattleManager::EndBattle()
{
#ifdef WITH_EDITOR
	UE_LOG(LogMain, Log, TEXT("End combat"));
#endif
}

void FBattleManager::ParticipantBeginTurn(ACharacterBase* turnOwner)
{

}

void FBattleManager::ParticipantEndTurn(ACharacterBase* turnOwner)
{

}

void FBattleManager::UpdateBattle()
{

}