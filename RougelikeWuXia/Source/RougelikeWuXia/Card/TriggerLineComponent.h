// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TriggerLineComponent.generated.h"

class UStaticMeshComponent;
class UStaticMesh;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROUGELIKEWUXIA_API UTriggerLineComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerLineComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ToggleVisibility(bool isShow);

	UFUNCTION(BlueprintCallable, category = "Card Trigger Line")
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
		bool IsTriggerLineVisible;

private:
	FVector CalculateLineMeshesPosition(float ratio);
};
