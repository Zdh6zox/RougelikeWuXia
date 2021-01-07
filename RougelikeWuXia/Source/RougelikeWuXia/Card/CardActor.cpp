// Fill out your copyright notice in the Description page of Project Settings.


#include "CardActor.h"
#include "UObject/ConstructorHelpers.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

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

	m_FrontWidgetComp = CreateDefaultSubobject<UWidgetComponent>("FrontWidget");
	m_FrontWidgetComp->SetupAttachment(CustomRoot);
	m_FrontWidgetComp->SetWidgetClass(m_FrontWidgetClass);


	m_BackWidgetComp = CreateDefaultSubobject<UWidgetComponent>("BackWigdet");
	m_BackWidgetComp->SetupAttachment(CustomRoot);
	m_BackWidgetComp->SetWidgetClass(m_BackWigdetClass);
}

// Called when the game starts or when spawned
void ACardActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACardActor::CardTransformTo(FCardTransformData destTrans)
{
	m_IsMoving = true;
	m_MovingRatio = 0.f;
	CardTransformData = destTrans;
	m_TargetTrans = CardTransformData.CardTransform;
}

// Called every frame
void ACardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_IsMoving)
	{
		m_MovingRatio += DeltaTime / TransformDuration;
		FVector curLoc = GetActorLocation();
		FRotator curRot = GetActorRotation();
		FVector curScale = GetActorScale3D();
		FVector newLoc = FMath::Lerp(curLoc, m_TargetTrans.GetLocation(), m_MovingRatio);
		FRotator newRot = FMath::Lerp(curRot, FRotator(m_TargetTrans.GetRotation()), m_MovingRatio);
		FVector newScale = FMath::Lerp(curScale, m_TargetTrans.GetScale3D(), m_MovingRatio);
		FTransform newTrans = FTransform(newRot, newLoc, newScale);

		SetActorTransform(newTrans);
		if (m_MovingRatio >= 1.0f)
		{
			m_IsMoving = false;
		}
	}
}

