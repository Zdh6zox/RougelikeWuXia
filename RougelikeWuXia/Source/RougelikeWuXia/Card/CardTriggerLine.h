// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardTriggerLine.generated.h"

class UStaticMeshComponent;
class UStaticMesh;
UCLASS()
class ROUGELIKEWUXIA_API ACardTriggerLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardTriggerLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleVisibility(bool isShow);
	void SetTriggerLinePosition(FVector startPos, FVector endPos);

	UPROPERTY(EditAnywhere)
		int ArrowMeshSize;

	UPROPERTY(EditAnywhere)
		UStaticMesh* ArrowMesh;

	UPROPERTY(EditAnywhere)
		UStaticMesh* ArrowHeadMesh;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* CustomRoot;

	UPROPERTY()
		UStaticMeshComponent* ArrowHead;

	UPROPERTY()
		TArray<UStaticMeshComponent*> ArrowMeshes;

	UPROPERTY()
		FVector StartPosition;

	UPROPERTY()
		FVector EndPosition;

	UPROPERTY()
		bool IsVisible;

private:
	void UpdateTriggerLine();
	FVector CalculateLineMeshesPosition(float ratio);
};
