// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLog.h"

void FBattleLog::AddLogEntry(FString EntryContent, TArray<FBattleLogEntryKeyWord> keyWords)
{
    FBattleLogEntry* newEntry = new FBattleLogEntry();
    newEntry->EntryContent = EntryContent;
    newEntry->KeyWords.Append(keyWords);

    m_Entrys.Add(MakeShareable(newEntry));
}

void FBattleLog::ClearLog()
{
    m_Entrys.Empty();
}