// Fill out your copyright notice in the Description page of Project Settings.


#include "CardManager.h"
#include "Managers/GameManager.h"

void FCardManager::InitializeManager(AGameManager* gm)
{
	m_GMCache = gm;
}