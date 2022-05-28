// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MAPGENERATOR_API FMap2DBorder
{
public:
    FMap2DBorder()
    {
        m_Length = 0.0f;
        m_Width = 0.0f;
    }
    FMap2DBorder(float length, float width)
    {
        m_Length = length;
        m_Width = width;
    }

    bool IsInsideMap(FVector2D relativePos, bool includingBorder = false) const;

private:
    float m_Length;
    float m_Width;
};
