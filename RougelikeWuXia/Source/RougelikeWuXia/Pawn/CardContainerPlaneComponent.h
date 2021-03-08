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
	enum EContainerMode
	{
		Strategy, 
		Skill,
		Ultimate
	};

	// Sets default values for this component's properties
	UCardContainerPlaneComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	    TArray<ACardActor*> ContainedStrategyCards;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<ACardActor*> ContainedSkillCards;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<ACardActor*> ContainedUltimateCards;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddNewCard(ACardActor* newCard);
	void RemoveCard(ACardActor* removingCard);

	void SetCurrentMode(EContainerMode newMode);
	inline EContainerMode GetCurrentMode() { return m_Mode; }

private:
	void RelocateDisplayingCards();
	void HideCurrentCards(bool toLeft);
	void FoldCards(EContainerMode curMode);
	void UnfoldCards(EContainerMode curMode);
	void DisplayCards(EContainerMode mode);
	bool CalculateCardTransform(int totalNum, int index, FTransform& globalTrans);

	USceneComponent* m_StrategySlotPivot;
	USceneComponent* m_SkillSlotPivot;
	USceneComponent* m_UltimateSlotPivot;
	ACardPawnWithCamera* m_OwnerPawnCache;
	EContainerMode m_Mode;
};
