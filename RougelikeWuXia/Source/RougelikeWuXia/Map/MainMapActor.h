// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapConstructor/MapConstructData.h"
#include "MapConstructor/MapConstructor.h"
#include "MainMapActor.generated.h"

class UMapData;
class AMapBlock;

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor, BlueprintCallable)
		void ConstructMap();

	UFUNCTION(BlueprintCallable)
		void LoadConstructedMap();

private:
	UPROPERTY(Transient)
		TArray<AMapBlock*> Blocks;

	void ConstructMap_Actual();

	FMapConstructor m_MapConstructor;
	int m_CurRow;
	int m_CurColumn;
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
