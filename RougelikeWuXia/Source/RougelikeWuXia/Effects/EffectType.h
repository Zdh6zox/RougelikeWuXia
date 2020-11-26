// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectType.generated.h"
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
