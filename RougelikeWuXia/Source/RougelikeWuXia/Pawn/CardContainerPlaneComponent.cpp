// Fill out your copyright notice in the Description page of Project Settings.


#include "CardContainerPlaneComponent.h"
#include "Card/CardActor.h"
#include "CardPawnWithCamera.h"
#include "Card/CardEnums.h"
#include "Card/CardBase.h"
#include "Engine/World.h"
#include "Managers/GameManager.h"
#include "UI/BattleScreenWidget.h"

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

	FString cardActorPath = "Blueprint'/Game/Card/CardActor_BP.CardActor_BP_C'";
	m_CardActorClass = LoadClass<ACardActor>(NULL, *cardActorPath);
	check(m_CardActorClass != NULL);
}


// Called every frame
void UCardContainerPlaneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (m_IsMoving && MovingDuration > 0.0f)
	{
		m_MovingRatio += DeltaTime / MovingDuration;
		FVector curLoc = GetRelativeLocation();
		FVector newLoc = FMath::Lerp(curLoc, m_TargetRelativeLoc, m_MovingRatio);

		SetRelativeLocation(newLoc);
		//FRotator newRot = FMath::Lerp(curRot, FRotator(m_TargetTrans.GetRotation()), m_MovingRatio);
		//FVector newScale = FMath::Lerp(curScale, m_TargetTrans.GetScale3D(), m_MovingRatio);
		//FTransform newTrans = FTransform(newRot, newLoc, newScale);

		//SetActorRelativeTransform(newTrans);
		if (m_MovingRatio >= 1.0f)
		{
			m_IsMoving = false;
		}
	}
}

void UCardContainerPlaneComponent::AddNewCard(ACardActor* newCard)
{
	switch (newCard->Card->GetCardType())
	{
	case ECardType::Strategy:
		ContainedStrategyCards.Insert(newCard, 0);
		newCard->AttachToComponent(m_StrategySlotPivot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		break;
	case ECardType::PositiveSkill:
		ContainedPositiveSkillCards.Insert(newCard, 0);
		newCard->AttachToComponent(m_PositiveSkillSlotPivot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		break;
	case ECardType::NegativeSkill:
		ContainedNegativeSkillCards.Insert(newCard, 0);
		newCard->AttachToComponent(m_NegativeSkillSlotPivot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		break;
	case ECardType::Ultimate:
		ContainedUltimateCards.Insert(newCard, 0);
		newCard->AttachToComponent(m_UltimateSlotPivot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		break;
	default:
		break;
	}

	RelocateDisplayingCards();
}

void UCardContainerPlaneComponent::AddNewCard(UCardBase* newCardBase)
{
	ACardActor* spawnedActor = GetWorld()->SpawnActor<ACardActor>(m_CardActorClass, m_DeckPivot->GetComponentTransform());
	spawnedActor->Card = newCardBase;

	AGameManager::GetGameManager(GetWorld())->BattleScreenWidget->AddCardEventSpy(spawnedActor);

	switch (newCardBase->GetCardType())
	{
	case ECardType::Strategy:
		ContainedStrategyCards.Insert(spawnedActor, 0);
		spawnedActor->AttachToComponent(m_StrategySlotPivot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		break;
	case ECardType::PositiveSkill:
		ContainedPositiveSkillCards.Insert(spawnedActor, 0);
		spawnedActor->AttachToComponent(m_PositiveSkillSlotPivot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		break;
	case ECardType::NegativeSkill:
		ContainedNegativeSkillCards.Insert(spawnedActor, 0);
		spawnedActor->AttachToComponent(m_NegativeSkillSlotPivot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		break;
	case ECardType::Ultimate:
		ContainedUltimateCards.Insert(spawnedActor, 0);
		spawnedActor->AttachToComponent(m_UltimateSlotPivot, FAttachmentTransformRules::SnapToTargetIncludingScale);
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
	case ECardType::PositiveSkill:
		ContainedPositiveSkillCards.Remove(removingCard);
		break;
	case ECardType::NegativeSkill:
		ContainedNegativeSkillCards.Remove(removingCard);
		break;
	case ECardType::Ultimate:
		ContainedUltimateCards.Remove(removingCard);
		break;
	default:
		break;
	}

	RelocateDisplayingCards();
}

void UCardContainerPlaneComponent::HideCurrentCards()
{
	FoldCards(m_CurrentType);
}

void UCardContainerPlaneComponent::FoldCards(EContainerSlotType curType)
{
	TArray<ACardActor*> foldingCards;
	switch (curType)
	{
	case UCardContainerPlaneComponent::Strategy:
		foldingCards = ContainedStrategyCards;
		break;
	case UCardContainerPlaneComponent::PositiveSkill:
		foldingCards = ContainedPositiveSkillCards;
		break;
	case UCardContainerPlaneComponent::NegativeSkill:
		foldingCards = ContainedNegativeSkillCards;
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

void UCardContainerPlaneComponent::UnfoldCards(EContainerSlotType curType)
{
	TArray<ACardActor*> unfoldingCards;
	switch (curType)
	{
	case UCardContainerPlaneComponent::Strategy:
		unfoldingCards = ContainedStrategyCards;
		break;
	case UCardContainerPlaneComponent::PositiveSkill:
		unfoldingCards = ContainedPositiveSkillCards;
		break;
	case UCardContainerPlaneComponent::NegativeSkill:
		unfoldingCards = ContainedNegativeSkillCards;
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

void UCardContainerPlaneComponent::DisplayCards(EContainerSlotType type)
{
	UnfoldCards(type);
}

void UCardContainerPlaneComponent::SetCurrentType(EContainerSlotType type)
{
	if (m_CurrentType == type)
	{
		return;
	}

	m_CurrentType = type;

	DisplayCards(m_CurrentType);
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
		finalLocation = finalLocation + FVector(1, 0, 0) * 0.01f * index;

		FTransform relativeTrans(rotationOffset, finalLocation);

		globalTrans = relativeTrans;
		return true;
	}

	return false;
}

void UCardContainerPlaneComponent::RelocateDisplayingCards()
{
	TArray<ACardActor*> displayingCards;
	if (m_CurrentType == EContainerSlotType::Strategy)
	{
		displayingCards = ContainedStrategyCards;
	}
	else if (m_CurrentType == EContainerSlotType::PositiveSkill)
	{
		displayingCards = ContainedPositiveSkillCards;
	}
	else if (m_CurrentType == EContainerSlotType::NegativeSkill)
	{
		displayingCards = ContainedNegativeSkillCards;
	}
	else if (m_CurrentType == EContainerSlotType::Ultimate)
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

void UCardContainerPlaneComponent::HideContainer()
{
	if (m_IsHiding)
	{
		return;
	}

	m_IsHiding = true;

	m_IsMoving = true;
	m_MovingRatio = 0;
	m_TargetRelativeLoc = GetRelativeLocation() + FVector(0, 0, -10);
}

void UCardContainerPlaneComponent::ShowContainer()
{
	if (!m_IsHiding)
	{
		return;
	}

	m_IsHiding = false;
	m_IsMoving = true;
	m_MovingRatio = 0;
	m_TargetRelativeLoc = GetRelativeLocation() + FVector(0, 0, 10);
}

void UCardContainerPlaneComponent::SetupSceneComponents(USceneComponent* strategyPivot, USceneComponent* positivePivot, USceneComponent* negativePivot
	, USceneComponent* ultimatePivot, USceneComponent* deckPivot, USceneComponent* discardedPivot)
{
	m_StrategySlotPivot = strategyPivot;
	m_StrategySlotPivot->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	m_PositiveSkillSlotPivot = positivePivot;
	m_PositiveSkillSlotPivot->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	m_NegativeSkillSlotPivot = negativePivot;
	m_NegativeSkillSlotPivot->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	m_UltimateSlotPivot = ultimatePivot;
	m_UltimateSlotPivot->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	m_DeckPivot = deckPivot;
	m_DeckPivot->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	m_DiscardedPivot = discardedPivot;
	m_DiscardedPivot->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
}