// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainBase.generated.h"

class UStaticMeshComponent;
class USceneComponent;
UCLASS()
class ROUGELIKEWUXIA_API ATerrainBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrainBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Terrain)
		USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Terrain)
		UStaticMeshComponent* BaseBlockMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
