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
	m_StrategySlotPivot = CreateDefaultSubobject<USceneComponent>("StrategySlotPivot");

	//m_StrategySlotPivot->RegisterComponent();
	m_StrategySlotPivot->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	m_SkillSlotPivot = CreateDefaultSubobject<USceneComponent>("SkillSlotPivot");

	//m_SkillSlotPivot->RegisterComponent();
	m_SkillSlotPivot->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	m_UltimateSlotPivot = CreateDefaultSubobject<USceneComponent>("UltimateSlotPivot");

	//m_UltimateSlotPivot->RegisterComponent();
	m_UltimateSlotPivot->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
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
	switch (newCard->Card->GetCardType())
	{
	case ECardType::Strategy:
		ContainedStrategyCards.Insert(newCard, 0);
		break;
	case ECardType::Skill:
		ContainedSkillCards.Insert(newCard, 0);
		break;
	case ECardType::Ultimate:
		ContainedUltimateCards.Insert(newCard, 0);
		break;
	default:
		break;
	}

	RelocateDisplayingCards();
}

void UCardContainerPlaneComponent::RemoveCard(ACardActor* removingCard)
{
	switch (removingCard->Card->GetCardType())
	{
	case ECardType::Strategy:
		ContainedStrategyCards.Remove(removingCard);
		break;
	case ECardType::Skill:
		ContainedSkillCards.Remove(removingCard);
		break;
	case ECardType::Ultimate:
		ContainedUltimateCards.Remove(removingCard);
		break;
	default:
		break;
	}

	RelocateDisplayingCards();
}

void UCardContainerPlaneComponent::HideCurrentCards(bool toLeft)
{
	FoldCards(m_Mode);
	if (toLeft)
	{
	}
}

void UCardContainerPlaneComponent::FoldCards(EContainerMode curMode)
{
	TArray<ACardActor*> foldingCards;
	switch (curMode)
	{
	case UCardContainerPlaneComponent::Strategy:
		foldingCards = ContainedStrategyCards;
		break;
	case UCardContainerPlaneComponent::Skill:
		foldingCards = ContainedSkillCards;
		break;
	case UCardContainerPlaneComponent::Ultimate:
		foldingCards = ContainedUltimateCards;
		break;
	default:
		break;
	}

	for (int i = 0; i < foldingCards.Num(); ++i)
	{
		FCardTransformData newCardTrans = foldingCards[i]->CardTransformData;
		newCardTrans.CardTransform = GetComponentTransform();
		foldingCards[i]->CardTransformTo(newCardTrans);
	}
}

void UCardContainerPlaneComponent::UnfoldCards(EContainerMode curMode)
{
	TArray<ACardActor*> unfoldingCards;
	switch (curMode)
	{
	case UCardContainerPlaneComponent::Strategy:
		unfoldingCards = ContainedStrategyCards;
		break;
	case UCardContainerPlaneComponent::Skill:
		unfoldingCards = ContainedSkillCards;
		break;
	case UCardContainerPlaneComponent::Ultimate:
		unfoldingCards = ContainedUltimateCards;
		break;
	default:
		break;
	}

	for (int i = 0; i < unfoldingCards.Num(); ++i)
	{
		FTransform newTrans;
		check(CalculateCardTransform(unfoldingCards.Num(), i, newTrans));
		FCardTransformData newCardTrans;
		newCardTrans.CardInHandIndex = i;
		newCardTrans.CardLocationType = ECardLocationType::InHand;
		newCardTrans.CardTransform = newTrans;
		unfoldingCards[i]->CardTransformTo(newCardTrans);
	}
}

void UCardContainerPlaneComponent::DisplayCards(EContainerMode mode)
{

}

void UCardContainerPlaneComponent::SetCurrentMode(EContainerMode newMode)
{
	if (m_Mode == newMode)
	{
		return;
	}

	m_Mode = newMode;
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

void UCardContainerPlaneComponent::RelocateDisplayingCards()
{
	TArray<ACardActor*> displayingCards;
	if (m_Mode == EContainerMode::Strategy)
	{
		displayingCards = ContainedStrategyCards;
	}
	else if (m_Mode == EContainerMode::Skill)
	{
		displayingCards = ContainedSkillCards;

	}
	else if (m_Mode == EContainerMode::Ultimate)
	{
		displayingCards = ContainedUltimateCards;
	}


	for (int i = 0; i < displayingCards.Num(); ++i)
	{
		ACardActor* card = displayingCards[i];

		FTransform newTrans;
		check(CalculateCardTransform(displayingCards.Num(), i, newTrans));
		FCardTransformData newCardTrans;
		newCardTrans.CardInHandIndex = i;
		newCardTrans.CardLocationType = ECardLocationType::InHand;
		newCardTrans.CardTransform = newTrans;
		card->CardTransformTo(newCardTrans);
	}
}