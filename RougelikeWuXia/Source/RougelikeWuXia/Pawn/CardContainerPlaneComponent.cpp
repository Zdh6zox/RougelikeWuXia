// Fill out your copyright notice in the Description page of Project Settings.


#include "CardContainerPlaneComponent.h"
#include "Card/CardActor.h"
#include "CardPawnWithCamera.h"
#include "Card/CardEnums.h"
#include "Card/CardBase.h"
#include "Managers/GameManager.h"

// Sets default values for this component's properties
UCardContainerPlaneComponent::UCardContainerPlaneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCardContainerPlaneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	ACardPawnWithCamera* ownerPawn = Cast<ACardPawnWithCamera>(GetOwner());
	check(ownerPawn);
}


// Called every frame
void UCardContainerPlaneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCardContainerPlaneComponent::AddNewCard(ACardActor* newCard)
{
	ContainedCards.Insert(newCard, 0);

	RelocateAllCards();
}

void UCardContainerPlaneComponent::RemoveCard(ACardActor* removingCard)
{
	ContainedCards.Remove(removingCard);

	RelocateAllCards();
}

bool UCardContainerPlaneComponent::CalculateCardTransform(int totalNum, int index, FTransform& globalTrans)
{
	FCardManager& cm = AGameManager::GetGameManager(GetWorld())->GetCardManager();

	FVector pivotOffset;
	FRotator rotationOffset;
	float radius;
	if (cm.GetInHandTransformPreset(totalNum,index,pivotOffset,rotationOffset,radius))
	{
		FVector finalVec = rotationOffset.RotateVector(FVector(0, 0, 1));
		FVector finalLocation = finalVec * radius + FVector(0, 0, -radius);
		//add little bias to avoid overlap
		finalLocation = finalLocation + FVector(1, 0, 0) * 0.01f*index;

		FTransform relativeTrans(rotationOffset, finalLocation);

		globalTrans = relativeTrans * GetComponentTransform();
		return true;
	}

	return false;
}

void UCardContainerPlaneComponent::RelocateAllCards()
{
	for (int i = 0; i < ContainedCards.Num(); ++i)
	{
		ACardActor* card = ContainedCards[i];

		FTransform newTrans;
		check(CalculateCardTransform(ContainedCards.Num(), i, newTrans));
		FCardTransformData newCardTrans;
		newCardTrans.CardInHandIndex = i;
		newCardTrans.CardLocationType = ECardLocationType::InHand;
		newCardTrans.CardTransform = newTrans;
		card->CardTransformTo(newCardTrans);
	}
}