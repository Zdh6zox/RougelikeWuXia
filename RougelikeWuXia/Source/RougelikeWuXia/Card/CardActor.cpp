// Fill out your copyright notice in the Description page of Project Settings.


#include "CardActor.h"
#include "UObject/ConstructorHelpers.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Managers/GameManager.h"
#include "Card/CardManager.h"
#include "Card/CardEvents.h"
#include "Card/CardEventChannel.h"

#pragma optimize("",off)
// Sets default values
ACardActor::ACardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> frontWidgetClass(TEXT("WidgetBlueprint'/Game/UI/CardWidget_Front.CardWidget_Front_C'"));
	if (frontWidgetClass.Class != NULL)
	{
		m_FrontWidgetClass = frontWidgetClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> backWidgetClass(TEXT("WidgetBlueprint'/Game/UI/CardWidget_Back.CardWidget_Back_C'"));
	if (backWidgetClass.Class != NULL)
	{
		m_BackWigdetClass = backWidgetClass.Class;
	}

	CustomRoot = CreateDefaultSubobject<USceneComponent>("Root");
	CustomRoot->Mobility = EComponentMobility::Movable;
	SetRootComponent(CustomRoot);

	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>("CardMesh");
	CardMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CardMesh->SetupAttachment(CustomRoot);

	FrontWidgetComp = CreateDefaultSubobject<UWidgetComponent>("FrontWidget");
	FrontWidgetComp->SetupAttachment(CustomRoot);
	FrontWidgetComp->SetWidgetClass(m_FrontWidgetClass);

	BackWidgetComp = CreateDefaultSubobject<UWidgetComponent>("BackWigdet");
	BackWidgetComp->SetupAttachment(CustomRoot);
	BackWidgetComp->SetWidgetClass(m_BackWigdetClass);

	CardBox = CreateDefaultSubobject<UBoxComponent>("CardBox");
	CardBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CardBox->SetupAttachment(CustomRoot);
}

ACardActor::~ACardActor()
{
	CardFocusedEvent_OneP.Clear();
	CardLostFocusEvent_OneP.Clear();
	CardSelectedEvent_OneP.Clear();
	CardUnselectedEvent_OneP.Clear();
	//CardTriggeredEvent_OneP.Clear();
	//CardAboutToTriggerEvent_OneP.Clear();
	CardCancelTriggerEvent_OneP.Clear();
}

// Called when the game starts or when spawned
void ACardActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACardActor::CardTransformTo(FCardTransformData destTrans)
{
	CardTransformData = destTrans;

	StartMovingTo(CardTransformData.CardTransform, InHandTransDuration);
	if (destTrans.CardLocationType == ECardLocationType::Discarded)
	{
		m_IsDiscarding = true;
	}
}

// Called every frame
void ACardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_IsMoving && m_CurTransDuration > 0.0f)
	{
		m_MovingRatio += DeltaTime / m_CurTransDuration;
		if (m_MovingRatio >= 1.0f)
		{
			SetActorRelativeTransform(m_TargetTrans);
			StopMoving();
			return;
		}

		FVector curLoc = m_OriginTrans.GetLocation();
		FRotator curRot = FRotator(m_OriginTrans.GetRotation());
		FVector curScale = m_OriginTrans.GetScale3D();
		FVector newLoc = FMath::Lerp(curLoc, m_TargetTrans.GetLocation(), m_MovingRatio);
		FRotator newRot = FMath::Lerp(curRot, FRotator(m_TargetTrans.GetRotation()), m_MovingRatio);
		FVector newScale = FMath::Lerp(curScale, m_TargetTrans.GetScale3D(), m_MovingRatio);
		FTransform newTrans = FTransform(newRot, newLoc, newScale);

		SetActorRelativeTransform(newTrans);
	}
}

void ACardActor::OnCardFocused()
{
	if (IsFocused)
	{
		return;
	}

	IsFocused = true;

	//Remove Roll
	FTransform curTrans = CardTransformData.CardTransform;
	FRotator curRot = FRotator(curTrans.GetRotation());
	curRot.Roll = 0.f;
	curTrans.SetRotation(FQuat(curRot));

	StartMovingTo(curTrans, DisplayTransDuration);

	CardFocusedEvent_OneP.Broadcast(this);
	CardFocusedEvent_BP();
}

void ACardActor::OnCardLostFocus()
{
	if (!IsFocused)
	{
		return;
	}

	IsFocused = false;
	StartMovingTo(CardTransformData.CardTransform, InHandTransDuration);
	CardLostFocusEvent_OneP.Broadcast(this);
	CardLostFocusEvent_BP();
}

void ACardActor::OnCardSelected()
{
	if (IsSelected)
	{
		return;
	}

	IsSelected = true;

	StopMoving();
	CardSelectedEvent_BP();
}

void ACardActor::OnCardUnselected()
{
	if (!IsSelected)
	{
		return;
	}

	IsSelected = false;

	FTransform curTrans = CardTransformData.CardTransform;
	StartMovingTo(curTrans, InHandTransDuration);

	CardUnselectedEvent_BP();
}

void ACardActor::OnCardTriggered()
{
	//FCardTriggeredEvent* triggeredEvent = new FCardTriggeredEvent();
	//triggeredEvent->TriggeredCard = this;

	//triggeredEvent->Broadcast(UCardEventChannel::GetChannel());
	//OnCardDiscarded();
}

void ACardActor::StartMovingTo(FTransform targetTrans, float time)
{
	m_IsMoving = true;
	m_MovingRatio = 0.f;

	m_OriginTrans = RootComponent->GetRelativeTransform();
	m_TargetTrans = targetTrans;
	m_CurTransDuration = time;
}

void ACardActor::StopMoving()
{
	m_IsMoving = false;
	m_MovingRatio = 0.0f;

	if (m_IsDiscarding)
	{
		CardDiscardedEvent_BP();
		Destroy();
	}
}

#pragma optimize("",on)
