// Fill out your copyright notice in the Description page of Project Settings.


#include "MapConstructDebugger.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

FMapConstructDebugger::~FMapConstructDebugger()
{
    for (int i = 0; i < m_DebugLogs.Num(); ++i)
    {
        delete m_DebugLogs[i];
    }

    m_DebugLogs.Empty();
}

void FMapConstructDebugger::AddDebugLog(FMapConstructDebugLog* newLog,bool increaseStep)
{
    if (increaseStep)
    {
        m_CurStep++;
    }
    newLog->Step = m_CurStep;
    m_DebugLogs.Add(newLog);
}

void FMapConstructDebugger::ShowDebug(const UWorld* world, float debugExistTime,int step)
{
    for (int i = m_CurDisplayIndex; i < m_DebugLogs.Num(); ++i)
    {
        if (m_DebugLogs[i]->Step >= step)
        {
            m_CurDisplayIndex = i;
            break;
        }

        FColor debugColor;
        float existingTime = debugExistTime;
        switch (m_DebugLogs[i]->ImportanceType)
        {
        case EMapConstructLogImportanceType::Main:
            debugColor = FColor::Green;
            break;
        case EMapConstructLogImportanceType::Procedure:
            debugColor = FColor::Blue;
            existingTime = 1.0f;
            break;
        case EMapConstructLogImportanceType::ErrorLog:
            debugColor = FColor::Red;
            existingTime = 1.0f;
            break;
        default:
            debugColor = FColor::Black;
            break;
        }

        switch (m_DebugLogs[i]->LogType)
        {
        case EMapConstructDebugLogType::Point:
            DrawDebugSphere(world, m_DebugLogs[i]->DebugLocation1, 1.0f, 16, debugColor, false, existingTime);
            break;
        case EMapConstructDebugLogType::Line:
            DrawDebugLine(world, m_DebugLogs[i]->DebugLocation1, m_DebugLogs[i]->DebugLocation2, debugColor, false, existingTime);
            break;
        case EMapConstructDebugLogType::Ring:
            DrawDebugCircle(world, m_DebugLogs[i]->DebugLocation1, m_DebugLogs[i]->DebugFloat1, 16, debugColor, false, existingTime);
            DrawDebugCircle(world, m_DebugLogs[i]->DebugLocation1, m_DebugLogs[i]->DebugFloat2, 16, debugColor, false, existingTime);
            break;
        case EMapConstructDebugLogType::Sphere:
            DrawDebugSphere(world, m_DebugLogs[i]->DebugLocation1, m_DebugLogs[i]->DebugFloat1, 16, debugColor, false, existingTime);
            break;
        case EMapConstructDebugLogType::Text:
            DrawDebugString(world, m_DebugLogs[i]->DebugLocation1, m_DebugLogs[i]->DebugString, nullptr, debugColor, existingTime);
            break;
        default:
            break;
        }
    }
}