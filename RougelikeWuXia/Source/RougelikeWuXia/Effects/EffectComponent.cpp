// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectComponent.h"
#include "Effects/EffectBase.h"
#include "Managers/GameManager.h"
#include "Managers/BattleManager.h"

// Sets default values for this component's properties
UEffectComponent::UEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	m_RoundFinishedHandle = AGameManager::GetGameManager(GetWorld())->GetBattleManager().RoundFinishedEvent_OneP.AddUObject(this, &UEffectComponent::RoundFinished);
}

void UEffectComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AGameManager::GetGameManager(GetWorld())->GetBattleManager().RoundFinishedEvent_OneP.Remove(m_RoundFinishedHandle);
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void UEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEffectComponent::ReceiveEffect(TSharedPtr<FEffectBase> newEffect)
{
	//add up same type effect
	for (auto& effect : m_CurrentEffects)
	{
		if (effect->GetEffectType() == newEffect->GetEffectType())
		{
			effect->IncreaseAmount(newEffect->GetAmount());
			return;
		}
	}

	m_CurrentEffects.Add(newEffect);
}

void UEffectComponent::RoundFinished(int curRoundNum)
{
	UE_LOG(LogEffect, Error, TEXT("%s Round %d finished"), *AActor::GetDebugName(GetOwner()), curRoundNum);
}
