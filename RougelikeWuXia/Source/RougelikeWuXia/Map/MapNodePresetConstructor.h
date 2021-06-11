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

#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere)
        FMapNodePreset PresetData;

    UPROPERTY(EditAnywhere)
        UDataTable* PresetTable;

	UPROPERTY(EditAnywhere)
		int CurrentDataTableRowIndex;
#endif
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR
    UFUNCTION(BlueprintCallable,CallInEditor)
        void ConstructFromData();

	UFUNCTION(BlueprintCallable, CallInEditor)
		void UpdateFromCurrent();

    UFUNCTION(BlueprintCallable, CallInEditor)
        void ImportFromDataTable();

    UFUNCTION(BlueprintCallable, CallInEditor)
        void ExportToDataTable();

private:
	void RemoveCurPreset();
    TArray<AMapNodeActor*> m_CurrentNodeUnits;
    TArray<AMapNodeLinkActor*> m_CurrentNodeLinks;
#endif
};
