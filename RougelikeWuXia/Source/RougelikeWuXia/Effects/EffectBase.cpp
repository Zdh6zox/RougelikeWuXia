// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBase.h"

DEFINE_LOG_CATEGORY(LogEffect)

void FEffectBase::TakeEffect()
{
	UE_LOG(LogEffect, Log, TEXT("%s take effect"), *GetEffectName());
}

FString FEffectBase::GetEffectName() const
{
	return "BaseEffect";
}

void FEffectBase::IncreaseAmount(int amount)
{
	m_Amount += amount;
}

void FEffectBase::ReduceAmount(int amount)
{
	if (m_Amount >= amount)
	{
		m_Amount -= amount;
	}
	else
	{
		m_Amount = 0;
	}
}

void FEffectBase::FinishTurn()
{
	UE_LOG(LogEffect, Log, TEXT("%s finish turn"), *GetEffectName());
	FinishTurn_Internal();
}

void FEffectBase::FinishRound()
{
	UE_LOG(LogEffect, Log, TEXT("%s finish round"), *GetEffectName());
	FinishRound_Internal();
}

void FEffectBase::FinishBattle()
{
	UE_LOG(LogEffect, Log, TEXT("%s finish battle"), *GetEffectName());
	FinishBattle_Internal();
}

void FEffectBase::OnAdded()
{
	UE_LOG(LogEffect, Log, TEXT("%s added"), *GetEffectName());
}

void FEffectBase::OnRemoved()
{
	UE_LOG(LogEffect, Log, TEXT("%s removed"), *GetEffectName());
}

bool FEffectBase::IsEffectFinished() const
{
	switch (m_SusbtainType)
	{
	case EEffectSustainType::Turns:
	case EEffectSustainType::Rounds:
	case EEffectSustainType::Battles:
		return m_Amount > 0;
	case EEffectSustainType::Permanent:
		return false;
	default:
		break;
	}

	return true;
}