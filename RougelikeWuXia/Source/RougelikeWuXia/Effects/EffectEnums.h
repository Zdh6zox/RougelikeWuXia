// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectEnums.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EEffectType : uint8
{
	Fragil,
	Vulnerable,
	ExtraDraw,
	AttributeUp,
	AttributeDown,
	PropertyUp,
	PropertyDown
};

UENUM(BlueprintType)
enum class EEffectSustainType : uint8
{
	Turns,
	Rounds,
	Battles,
	Permanent
};
