// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Card/CardData.h"
#include "GameBPFunctionLibrary.generated.h"

class UCardBase;
class AGameManager;
class UWorld;
/**
 * 
 */
UCLASS()
class ROUGELIKEWUXIA_API UGameBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Card BP Function")
        static UCardBase* CreateNewCard(UObject* outer, int cardID);

    UFUNCTION(BlueprintCallable, Category = "Basic BP Function")
        static AGameManager* GetGameManager(UWorld* world);
};
