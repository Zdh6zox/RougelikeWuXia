﻿// Fill out your copyright notice in the Description page of Project Settings.

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
    Item UMETA(DisplayName = "物品"),
    Skill UMETA(DisplayName = "招式"),
    Intention UMETA(DisplayName = "意图")
};
