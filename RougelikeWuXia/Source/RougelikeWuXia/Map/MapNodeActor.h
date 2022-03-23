// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapNodeActor.generated.h"

class UPaperSpriteComponent;
class UMapNode;
class UTextRenderComponent;
UCLASS(abstract)
class ROUGELIKEWUXIA_API AMapNodeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapNodeActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* CustomRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPaperSpriteComponent* SpriteComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UTextRenderComponent* TextRenderer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ActorName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TextSize = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform OffsetTransform;

	UPROPERTY()
		UMapNode* Node;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NodeImpactRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool ShowImpactRadius = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DebugDisplay();

private:
	void DebugDisplayImpactRadius();
	bool CheckHasNodeNearby();
};
