// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effects/EffectBase.h"
/**
 * 
 */
class ROUGELIKEWUXIA_API FAttributeModifyEffect : public FEffectBase
{
public:
	typedef FEffectBase Super;
public:
	virtual void TakeEffect() override;
	virtual FString GetEffectName() const override;

	virtual void FinishBattle_Internal() override;
	virtual void FinishRound_Internal() override;
	virtual void FinishTurn_Internal() override;
};
