// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectEnums.h"


DECLARE_LOG_CATEGORY_EXTERN(LogEffect, Log, All);
/**
 * 
 */
class ROUGELIKEWUXIA_API FEffectBase
{
public:
	virtual void TakeEffect();
	virtual FString GetEffectName() const;

	virtual void OnAdded();
	virtual void OnRemoved();

	void FinishTurn();
	void FinishRound();
	void FinishBattle();

	virtual void FinishTurn_Internal() = 0;
	virtual void FinishRound_Internal() = 0;
	virtual void FinishBattle_Internal() = 0;

	bool IsEffectFinished() const;

	void IncreaseAmount(int amount);
	void ReduceAmount(int amount);

	inline EEffectType GetEffectType() const { return m_EffectType; }

	inline int GetAmount() const { return m_Amount; }
private:
	
	EEffectType m_EffectType;
	EEffectSustainType m_SusbtainType;
	int m_Amount = 0;
};
