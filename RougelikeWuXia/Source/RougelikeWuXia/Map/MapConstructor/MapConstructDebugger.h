// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
enum EMapConstructDebugLogType
{
    Point,
    Line,
    Ring,
    Sphere
};

class FMapConstrcutDebugLog
{
public:
    EMapConstructDebugLogType LogType;

};

class FMapConstructDebugger
{
public:
    void AddDebugLog();
    void ShowDebug();

private:
    TMap<int32, FMapConstrcutDebugLog> m_DebugLogs;
};
