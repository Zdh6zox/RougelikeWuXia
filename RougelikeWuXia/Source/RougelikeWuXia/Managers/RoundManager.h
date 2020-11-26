// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class AGameManager;
class ROUGELIKEWUXIA_API FRoundManager
{
public:
	void Initialize(AGameManager* gm);

private:
	AGameManager* m_GameManager;
};
