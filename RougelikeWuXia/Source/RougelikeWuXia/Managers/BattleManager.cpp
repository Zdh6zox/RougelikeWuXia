// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"
#include "GameManager.h"


void FBattleManager::Initialize(AGameManager* gm)
{
	m_GameManager = gm;
}