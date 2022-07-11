// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGeneratorIncludes.h"
#include "MapGeneratorTestActor.generated.h"


class FMap2DGenerationResult;
UCLASS()
class MAPGENERATOR_API AMapGeneratorTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGeneratorTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
		void DebugGenerate2DMap();

public:
	UPROPERTY(EditAnywhere)
		FMapGenerator2DSetting Map2DGenerationSetting;

	UPROPERTY(EditAnywhere)
		float SiteDisplayRadius;

    UPROPERTY(EditAnywhere)
        FColor SiteDisplayColor;

    UPROPERTY(EditAnywhere)
		FColor EdgeDisplayColor;

private:
	void Display2DMapGenerationResult(FMap2DGenerationResult* result);
};
