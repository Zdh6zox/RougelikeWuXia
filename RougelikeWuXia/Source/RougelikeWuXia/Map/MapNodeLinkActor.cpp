// Fill out your copyright notice in the Description page of Project Settings.


#include "MapNodeLinkActor.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"

// Sets default values
AMapNodeLinkActor::AMapNodeLinkActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRoot = CreateDefaultSubobject<USceneComponent>("Root");
	CustomRoot->Mobility = EComponentMobility::Movable;
	SetRootComponent(CustomRoot);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("LinkSprite");
	SpriteComponent->SetupAttachment(CustomRoot);
}

// Called when the game starts or when spawned
void AMapNodeLinkActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapNodeLinkActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

