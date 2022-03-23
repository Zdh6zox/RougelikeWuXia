// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapConstructor/MapConstructData.h"
#include "MainMapActor.generated.h"

class UMapData;
class AMapBlock;
class FMapConstructor;

UCLASS()
class ROUGELIKEWUXIA_API AMainMapActor : public AActor
{
	GENERATED_BODY()

	friend class FMapConstructAsyncTask;

public:	
	// Sets default values for this actor's properties
	AMainMapActor();

	UPROPERTY(EditAnywhere)
		FMapConstructData MapConstructData;

	UPROPERTY()
		UMapData* MapData;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AMapBlock> BlockClass;

	UPROPERTY(EditAnywhere)
		int BlockConstructOneFrame;

	UPROPERTY(VisibleAnywhere, Transient)
		bool ConstructCompleted = false;

	UPROPERTY(VisibleAnywhere, Transient)
		TArray<FVector2D> GeneratedMainLocs;

    UPROPERTY(VisibleAnywhere, Transient)
        TArray<FVector2D> GeneratedSubLocs;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void DebugGenMainCityLocs();

    UFUNCTION(BlueprintCallable)
        void DebugDividRegion();

    UFUNCTION(BlueprintCallable)
        void DebugGenSubNodesLocs();

    UFUNCTION(BlueprintCallable)
        void DebugSpawnActors();

    UFUNCTION(BlueprintCallable)
        void DebugGenLinks();

private:
	UPROPERTY(Transient)
		TArray<AMapBlock*> Blocks;

	void ConstructMap_Actual();

	void TriggerDisplayStep();

	FMapConstructor* m_MapConstructor = nullptr;
	int m_CurRow;
	int m_CurColumn;
	bool m_ShowDebug = false;
	FTimerHandle m_DebugDisplayTimer;
};

class FMapConstructAsyncTask : public FNonAbandonableTask
{
	friend class FAsyncTask<FMapConstructAsyncTask>;

public:
	FMapConstructAsyncTask(AMainMapActor* mainMapActor)
		: m_MainMapActor(mainMapActor)
	{
	}

	void DoWork()
	{
		if (m_MainMapActor)
		{
			m_MainMapActor->ConstructMap_Actual();
		}
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FMapConstructAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}

private:
	AMainMapActor* m_MainMapActor;
};
