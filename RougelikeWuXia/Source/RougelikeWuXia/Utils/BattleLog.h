// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class FBattleLogEntryType
{
    Phase,
    Card,
    Effect
};

struct FBattleLogEntryKeyWord
{
public:
    FString KeyWordContent;
};

class ROUGELIKEWUXIA_API FBattleLogEntry
{
public:
    void PrintLog(FString& outLog);

    FBattleLogEntryType EntryType;
    FString EntryContent;
    TArray<FBattleLogEntryKeyWord> KeyWords;
};
/**
 * 
 */
class ROUGELIKEWUXIA_API FBattleLog
{
public:
    void AddLogEntry(FString EntryContent, TArray<FBattleLogEntryKeyWord> keyWords);
    void ClearLog();
private:
    TArray<TSharedPtr<FBattleLogEntry>> m_Entrys;
};
