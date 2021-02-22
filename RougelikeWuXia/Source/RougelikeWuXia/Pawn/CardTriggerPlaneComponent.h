// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CardTriggerPlaneComponent.generated.h"

class UBoxComponent;
class ACardPawnWithCamera;
class ACardActor;
class UStaticMesh;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ROUGELIKEWUXIA_API UCardTriggerPlaneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCardTriggerPlaneComponent();

	UPROPERTY(EditAnywhere)
		int ArrowSize = 0;

	UPROPERTY(EditAnywhere)
		UStaticMesh* ArrowMesh;

	UPROPERTY(EditAnywhere)
		UStaticMesh* ArrowHeadMesh;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetQueryPlane(UStaticMeshComponent* plane);
	void SetTriggerBox(UBoxComponent* triggerBox);

	bool IsCardInsideBox(ACardActor* cardActor);

private:
	UStaticMeshComponent* m_QueryPlane;
	UBoxComponent* m_TriggerBox;
	UStaticMeshComponent* m_ArrowHeadMeshComp;
	TArray<UStaticMeshComponent*> m_ArrowMeshComps;
};
