// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectType.h"


DECLARE_LOG_CATEGORY_EXTERN(LogEffect, Log, All);
/**
 * 
 */
class ACharacterBase;
class ROUGELIKEWUXIA_API FEffectBase
{
public:
	virtual void TakeEffect(ACharacterBase* receiver);
	virtual FString GetEffectName() const;
	virtual bool IsEffectFinished() { return false; }

	void IncreaseAmount(int amount);
	void ReduceAmount(int amount);

	inline EEffectType GetEffectType() const { return m_EffectType; }

	inline int GetAmount() const { return m_Amount; }
	virtual bool IsPermanent() const { return false; }
private:
	ACharacterBase* m_Sender;
	EEffectType m_EffectType;
	int m_Amount = 0;
};
