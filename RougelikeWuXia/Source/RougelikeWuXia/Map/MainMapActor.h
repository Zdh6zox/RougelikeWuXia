// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapConstructData.h"
#include "MapConstructor.h"
#include "MainMapActor.generated.h"

class UMapData;

UCLASS()
class ROUGELIKEWUXIA_API AMainMapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainMapActor();

	UPROPERTY()
		FMapConstructData MapConstructData;

	UPROPERTY()
		UMapData* MapData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
		void ConstructMap();

	UFUNCTION(BlueprintCallable)
		void LoadConstructedMap();

private:
	FMapConstructor m_MapConstructor;
};
