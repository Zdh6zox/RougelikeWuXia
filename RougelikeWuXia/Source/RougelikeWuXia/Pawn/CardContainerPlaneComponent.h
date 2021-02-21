// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CardContainerPlaneComponent.generated.h"

class ACardActor;
class UCardBase;
class ACardPawnWithCamera;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ROUGELIKEWUXIA_API UCardContainerPlaneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCardContainerPlaneComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ACardActor*> ContainedCards;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddNewCard(ACardActor* newCard);
	void RemoveCard(ACardActor* removingCard);

private:
	void RelocateAllCards();
	bool CalculateCardTransform(int totalNum, int index, FTransform& globalTrans);

	ACardPawnWithCamera* m_OwnerPawnCache;
};
