// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MAPGENERATOR_API FMap2DEdge
{
public:
	FMap2DEdge(FVector2D startPos, FVector2D endPos, bool hasDirection = false)
	{
		m_StartPos = startPos;
		m_EndPos = endPos;
		m_HasDirection = hasDirection;
	}

private:
	FVector2D m_StartPos;
	FVector2D m_EndPos;
	bool m_HasDirection = false;
};
