// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETerrainBasicType : uint8
{
	Base UMETA(DisplayName = "基础"),
	Trajectory UMETA(DisplayName = "轨迹"),
	//Secondary UMETA(DisplayName = "")
	Exit UMETA(DisplayName = "出口")
};

UENUM(BlueprintType)
enum class ETerrainSubType : uint8
{
	Base_Mud UMETA(DisplayName = "泥地"),
	Base_Brick,
	Base_Wood
};