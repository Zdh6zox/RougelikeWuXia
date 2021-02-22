// Fill out your copyright notice in the Description page of Project Settings.


#include "CardPawnWithCamera.h"
#include "Camera/CameraComponent.h"
#include "CardTriggerPlaneComponent.h"
#include "CardContainerPlaneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Managers/GameManager.h"
#include "ScreenOnlyPlayerController.h"
#include "Card/CardActor.h"
#include "Card/CardBase.h"
#include "PlayerRuntimeData.h"

// Sets default values
ACardPawnWithCamera::ACardPawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRoot = CreateDefaultSubobject<USceneComponent>("Root");
	CustomRoot->Mobility = EComponentMobility::Movable;
	SetRootComponent(CustomRoot);

	MainCameraComponent = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCameraComponent->SetupAttachment(CustomRoot);

	CardContainer = CreateDefaultSubobject<UCardContainerPlaneComponent>("CardContainerPlane");
	CardContainer->Mobility = EComponentMobility::Movable;
	CardContainer->SetupAttachment(CustomRoot);

	QueryPlane = CreateDefaultSubobject<UStaticMeshComponent>("QueryPlane");
	QueryPlane->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");

	TriggerPlane = CreateDefaultSubobject<UCardTriggerPlaneComponent>("CardTriggerPlane");
	TriggerPlane->Mobility = EComponentMobility::Movable;
	TriggerPlane->SetQueryPlane(QueryPlane);
	TriggerPlane->SetTriggerBox(TriggerBox);
	QueryPlane->SetupAttachment(TriggerPlane);
	TriggerBox->SetupAttachment(TriggerPlane);
	TriggerPlane->SetupAttachment(CustomRoot);
}

// Called when the game starts or when spawned
void ACardPawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACardPawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AScreenOnlyPlayerController* playerCon = Cast<AScreenOnlyPlayerController>(GetController());
	if (playerCon == nullptr)
	{
		return;
	}

	if (m_CurrentPhase == Browse)
	{
		FHitResult hitResult;
		playerCon->GetHitResultUnderCursor(ECC_WorldDynamic, false, hitResult);
		if (hitResult.bBlockingHit)
		{
			AActor* hittedActor = hitResult.Actor.Get();
			ACardActor* hittedCardActor = Cast<ACardActor>(hittedActor);
			ActorHittedUnderCursorEvent_BP(hittedActor, true);
			
			SetCurFocusedCard(hittedCardActor);

			if (hittedCardActor != NULL && playerCon->WasJustTriggered())
			{
				SetCurSelectedCard(hittedCardActor);
				m_CurrentPhase = MovingCard;
			}
		}
	}
	else if (m_CurrentPhase == MovingCard)
	{
		if (playerCon->WasJustReleased())
		{
			SetCurSelectedCard(NULL);
			m_CurrentPhase = Browse;
			return;
		}

		FHitResult hitResult;
		playerCon->GetHitResultUnderCursor(ECC_PhysicsBody, false, hitResult);
		if (hitResult.bBlockingHit)
		{
			AActor* hittedActor = hitResult.Actor.Get();
			ActorHittedUnderCursorEvent_BP(hittedActor, false);
			if (hittedActor == this)
			{
				m_CurSelectedCard->SetActorLocation(hitResult.ImpactPoint);

				if (TriggerPlane->IsCardInsideBox(m_CurSelectedCard))
				{
					m_CurrentPhase = Triggering;
				}
			}
		}
	}
	else if (m_CurrentPhase == Triggering)
	{
		if (playerCon->WasJustReleased())
		{
			m_CurrentPhase = Browse;

			m_CurSelectedCard->OnCardTriggered();
			DiscardCard(m_CurSelectedCard);
			SetCurSelectedCard(NULL);
			return;
		}
	}
}

// Called to bind functionality to input
void ACardPawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACardPawnWithCamera::DrawCard()
{
	AGameManager* gm = AGameManager::GetGameManager(GetWorld());
	int drawingCardDeckIndex = gm->GetRandomStream().RandRange(0, m_CardsInDeck.Num() - 1);
	UCardBase* drawingCard = m_CardsInDeck[drawingCardDeckIndex];
	m_CardsInDeck.RemoveAt(drawingCardDeckIndex);

	FCardManager& cardManager = gm->GetCardManager();
	ACardActor* spawnedCard = cardManager.SpawnCardActor(drawingCard);

	CardContainer->AddNewCard(spawnedCard);
}

void ACardPawnWithCamera::DiscardCard(ACardActor* discardingCard)
{
	CardContainer->RemoveCard(discardingCard);
}

void ACardPawnWithCamera::SetCurFocusedCard(ACardActor* focusedCard)
{
	if (m_CurFocusedCard == focusedCard)
	{
		return;
	}

	if (m_CurFocusedCard != NULL)
	{
		//if previous focused is not null
		m_CurFocusedCard->OnCardLostFocus();
	}

	m_CurFocusedCard = focusedCard;
	if (m_CurFocusedCard != NULL)
	{
		m_CurFocusedCard->OnCardFocused();
	}
}

void ACardPawnWithCamera::SetCurSelectedCard(ACardActor* selectedCard)
{
	if (m_CurSelectedCard == selectedCard)
	{
		return;
	}

	if (m_CurSelectedCard != NULL)
	{
		//if previous selected is not null
		m_CurSelectedCard->OnCardUnselected();
	}

	m_CurSelectedCard = selectedCard;
	if (m_CurSelectedCard != NULL)
	{
		m_CurSelectedCard->OnCardSelected();
	}
}

void ACardPawnWithCamera::OnBattleBegin()
{
	if (m_PlayerData != nullptr)
	{
		//construct deck from player data
		for (auto& cardRuntimeData : m_PlayerData->PlayerOwnedCards)
		{
			UCardBase* newCard = NewObject<UCardBase>();
			newCard->InitializeFromCardRuntimeData(cardRuntimeData);

			m_CardsInDeck.Add(newCard);
		}
	}
}

void ACardPawnWithCamera::TestBattleBeginFired()
{

}

void ACardPawnWithCamera::TestDrawNewCard()
{

}

void ACardPawnWithCamera::TestCreateDeck()
{
	FCardManager& cardManager = AGameManager::GetGameManager(GetWorld())->GetCardManager();
	for (int i = 0; i < 12; ++i)
	{
		UCardBase* newCard = cardManager.CreateCardViaCardID(i);
		m_CardsInDeck.Add(newCard);
	}
}