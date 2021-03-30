// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainConstructor.generated.h"

class ATerrainBase;

UCLASS()
class ROUGELIKEWUXIA_API ATerrainConstructor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrainConstructor();

	UPROPERTY(EditAnywhere)
		float TerrainSize = 50.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ConstructTerrain(int rowNum, int columnNum);

	UFUNCTION(BlueprintCallable)
		void Test_ConstrctTerrain(int rowNum, int columnNum);

private:
	TArray<ATerrainBase*> m_Terrains;
};
