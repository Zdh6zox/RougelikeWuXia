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



	USceneComponent* rootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	rootComponent->Mobility = EComponentMobility::Static;
	SetRootComponent(rootComponent);

	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>("CardMesh");
	CardMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CardMesh->SetupAttachment(rootComponent);

	m_FrontWidgetComp = CreateDefaultSubobject<UWidgetComponent>("FrontWidget");
	m_FrontWidgetComp->SetupAttachment(rootComponent);
	m_FrontWidgetComp->SetWidgetClass(m_FrontWidgetClass);


	m_BackWidgetComp = CreateDefaultSubobject<UWidgetComponent>("BackWigdet");
	m_BackWidgetComp->SetupAttachment(rootComponent);
	m_BackWidgetComp->SetWidgetClass(m_BackWigdetClass);
}

// Called when the game starts or when spawned
void ACardActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

