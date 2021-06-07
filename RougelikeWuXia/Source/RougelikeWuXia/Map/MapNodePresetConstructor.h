// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapNodePreset.h"
#include "MapNodePresetConstructor.generated.h"


class AMapNodeActor;
class AMapNodeLinkActor;
UCLASS()
class ROUGELIKEWUXIA_API AMapNodePresetConstructor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapNodePresetConstructor();

    UPROPERTY(EditAnywhere)
        FMapNodePreset PresetData;

    UPROPERTY(EditAnywhere)
        UDataTable* PresetTable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable,CallInEditor)
        void ConstructFromData();

    UFUNCTION(BlueprintCallable)
        void ImportFromDataTable(int rowIndex);

    UFUNCTION(BlueprintCallable)
        void CreateNewData();

    UFUNCTION(BlueprintCallable)
        void ExportToDataTable();

private:
    TArray<AMapNodeActor*> m_CurrentNodeUnits;
    TArray<AMapNodeLinkActor*> m_CurrentNodeLinks;
};
