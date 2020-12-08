// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Effects/EffectBase.h"
#include "RougelikeWuXia.h"
#include "Managers/BattleManager.h"
#include "Managers/GameManager.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	FBattleManager bm = AGameManager::GetGameManager(GetWorld())->GetBattleManager();
	m_BattleStartHandle = bm.BattleStartedEvent_OneP.AddUObject(this, &ACharacterBase::OnBattleStart);
	m_BattleFinishedHandle = bm.BattleFinishedEvent_OneP.AddUObject(this, &ACharacterBase::OnBattleFinished);
	m_TurnBeginHandle = bm.TurnBeginEvent_OneP.AddUObject(this, &ACharacterBase::OnTurnBegin);
	m_TurnEndHandle = bm.TurnEndEvent_OneP.AddUObject(this, &ACharacterBase::OnTurnEnd);
	m_RoundStartHandle = bm.RoundStartedEvent_OneP.AddUObject(this, &ACharacterBase::OnRoundStart);
	m_RoundFinishedHandle = bm.RoundFinishedEvent_OneP.AddUObject(this, &ACharacterBase::OnRoundFinished);
}

void ACharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	FBattleManager bm = AGameManager::GetGameManager(GetWorld())->GetBattleManager();
	bm.BattleStartedEvent_OneP.Remove(m_BattleStartHandle);
	bm.BattleFinishedEvent_OneP.Remove(m_BattleFinishedHandle);
	bm.TurnBeginEvent_OneP.Remove(m_TurnBeginHandle);
	bm.TurnEndEvent_OneP.Remove(m_TurnEndHandle);
	bm.RoundStartedEvent_OneP.Remove(m_RoundStartHandle);
	bm.RoundFinishedEvent_OneP.Remove(m_RoundFinishedHandle);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::OnRoundStart(int roundNum)
{

}

void ACharacterBase::OnRoundFinished(int roundNum)
{

}

void ACharacterBase::OnTurnBegin(ACharacterBase* turnOwner)
{

}

void ACharacterBase::OnTurnEnd(ACharacterBase* turnOwner)
{

}

void ACharacterBase::OnBattleStart(const TArray<ACharacterBase *> participants)
{

}

void ACharacterBase::OnBattleFinished(const TArray<ACharacterBase *> participants)
{

}