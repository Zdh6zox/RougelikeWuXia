// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapConstructDebugger.generated.h"

/**
 * 
 */
class UWorld;
UENUM(BlueprintType)
enum EMapConstructPhaseType
{
    GenerateMainCity,
    GenerateRegion,
    GenerateTerrain,
    GenerateSubNodes
};

enum EMapConstructDebugLogType
{
    Point,
    Line,
    Ring,
    Sphere,
    Text
};

enum EMapConstructLogImportanceType
{
    Main,
    Procedure,
    ErrorLog,
    Period
};

class FMapConstructDebugLog
{
public:
    EMapConstructLogImportanceType ImportanceType;
    EMapConstructDebugLogType LogType;
    FVector DebugLocation1;
    FVector DebugLocation2;
    FString DebugString;
    float DebugFloat1;
    float DebugFloat2;
    int Step;
};

//TODO:
//add sub step debug display

class FMapConstructDebugger
{
public:
    FMapConstructDebugger(EMapConstructPhaseType phase)
    {
        m_PhaseType = phase;
    }
    ~FMapConstructDebugger();
    void AddDebugLog(FMapConstructDebugLog* newLog,bool increaseStep);
    void ShowDebug(const UWorld* world, float debugExistTime,int step);
    EMapConstructPhaseType GetPhaseType() const { return m_PhaseType; }

private:
    EMapConstructPhaseType m_PhaseType;
    TArray<FMapConstructDebugLog*> m_DebugLogs;
    int m_CurStep;
    int m_CurDisplayIndex;
};
