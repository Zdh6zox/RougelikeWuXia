// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ERoundPhaseType : uint8
{
	RoundStart,
	PlayerPhase,
	PlayerAttackPhase,
	ParticipantTurnStart,
	ParticipantTurnExecute,
	ParticipantTurnEnd,
	RoundEnd
};

UENUM(BlueprintType)
enum class EBattlePhaseType : uint8
{
	NotInBattle,
	BattleStart,
	MainPhase,
	Settlement
};
