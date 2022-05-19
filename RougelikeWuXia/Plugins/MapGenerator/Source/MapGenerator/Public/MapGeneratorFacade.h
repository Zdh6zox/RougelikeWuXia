// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MAPGENERATOR_API FMapGeneratorFacade
{
public:
    static void Generate2DMapPOILocation();
    static void Generate2DMapPathes();
    static void Generate3DMapPOILocation();
    static void Generate3DMapPathes();
};
