// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBase.h"

DEFINE_LOG_CATEGORY(LogEffect)

void FEffectBase::TakeEffect(ACharacterBase* receiver)
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