// Fill out your copyright notice in the Description page of Project Settings.


#include "CardMovingPlane.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Card/CardActor.h"

// Sets default values
ACardMovingPlane::ACardMovingPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CustomRoot = CreateDefaultSubobject<USceneComponent>("Root");
	CustomRoot->Mobility = EComponentMobility::Movable;
	SetRootComponent(CustomRoot);

	CardMovingPlane = CreateDefaultSubobject<UStaticMeshComponent>("MovingPlane");
	CardMovingPlane->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CardMovingPlane->SetupAttachment(CustomRoot);

	CardTriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	CardTriggerBox->SetupAttachment(CustomRoot);
}

// Called when the game starts or when spawned
void ACardMovingPlane::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACardMovingPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACardMovingPlane::IsCardInsideTriggerBox(ACardActor* card) const
{
	return CardTriggerBox->IsOverlappingActor(card);
}