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
	enum EContainerSlotType
	{
		Strategy = 0,
		PositiveSkill,
		NegativeSkill,
		Ultimate,
		Count
	};

	// Sets default values for this component's properties
	UCardContainerPlaneComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	    TArray<ACardActor*> ContainedStrategyCards;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<ACardActor*> ContainedPositiveSkillCards;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<ACardActor*> ContainedNegativeSkillCards;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<ACardActor*> ContainedUltimateCards;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MovingDuration = 2.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddNewCard(ACardActor* newCard);
	void RemoveCard(ACardActor* removingCard);
	void AddNewCard(UCardBase* newCardBase);

	void ShowContainer();
	void HideContainer();

	void SetCurrentType(EContainerSlotType newType);
	inline EContainerSlotType GetCurrentType() { return m_CurrentType; }

	void SetupSceneComponents(USceneComponent* strategyPivot, USceneComponent* positivePivot, USceneComponent* negativePivot, USceneComponent* ultimatePivot,
		USceneComponent* deckPivot, USceneComponent* discardedPivot);

private:
	void RelocateDisplayingCards();
	void HideCurrentCards();
	void FoldCards(EContainerSlotType curMode);
	void UnfoldCards(EContainerSlotType curMode);
	void DisplayCards(EContainerSlotType mode);
	bool CalculateCardTransform(int totalNum, int index, FTransform& globalTrans);

	USceneComponent* m_StrategySlotPivot;
	USceneComponent* m_PositiveSkillSlotPivot;
	USceneComponent* m_NegativeSkillSlotPivot;
	USceneComponent* m_UltimateSlotPivot;
	USceneComponent* m_DeckPivot;
	USceneComponent* m_DiscardedPivot;
	ACardPawnWithCamera* m_OwnerPawnCache;
	EContainerSlotType m_CurrentType;
	bool m_IsHiding = false;
	bool m_IsMoving = false;
	float m_MovingRatio = 0.f;
	FVector m_TargetRelativeLoc = FVector::ZeroVector;

private:
	UClass* m_CardActorClass;
};
