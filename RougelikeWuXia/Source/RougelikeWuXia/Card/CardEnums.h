// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESkillCardType : uint8
{
	Offense UMETA(DisplayName = "攻击"),
	Defense UMETA(DisplayName = "防御")
};

UENUM(BlueprintType)
enum class ECardNatureType : uint8
{
	Yang UMETA(DisplayName = "阳"),
	Yin UMETA(DisplayName = "阴"),
	Neutral UMETA(DisplayName = "中庸")
};

UENUM(BlueprintType)
enum class ECardType : uint8
{
    Strategy UMETA(DisplayName = "谋"),
	PositiveSkill UMETA(DisplayName = "攻"),
	NegativeSkill UMETA(DisplayName = "御"),
    Ultimate UMETA(DisplayName = "绝")
};

UENUM(BlueprintType)
enum class ECardLocationType : uint8
{
	Deck UMETA(DisplayName = "牌组"),
	External UMETA(DisplayName = "额外"),
	InHand UMETA(DisplayName = "手牌"),
	Discarded UMETA(DisplayName = "废弃"),
	Destroyed UMETA(DisplayName = "销毁")
};
