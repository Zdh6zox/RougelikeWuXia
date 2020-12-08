// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Managers/BattleManager.h"
#include "Managers/GameManager.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	FBattleManager bm = AGameManager::GetGameManager(GetWorld())->GetBattleManager();
	m_PlayerSetupStartHandle = bm.PlayerSetupPhaseStartEvent_NoP.AddUObject(this, &APlayerCharacter::OnPlayerSetupBegin);
	m_PlayerSetupFinishedHandle = bm.PlayerSetupPhaseEndEvent_NoP.AddUObject(this, &APlayerCharacter::OnPlayerSetupEnd);
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	FBattleManager bm = AGameManager::GetGameManager(GetWorld())->GetBattleManager();
	bm.PlayerSetupPhaseStartEvent_NoP.Remove(m_PlayerSetupStartHandle);
	bm.PlayerSetupPhaseEndEvent_NoP.Remove(m_PlayerSetupFinishedHandle);
}

void APlayerCharacter::OnPlayerSetupBegin()
{

}

void APlayerCharacter::OnPlayerSetupEnd()
{

}