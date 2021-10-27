// Fill out your copyright notice in the Description page of Project Settings.


#include "MapNodeActor.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "MapNode.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"

// Sets default values
AMapNodeActor::AMapNodeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRoot = CreateDefaultSubobject<USceneComponent>("Root");
	CustomRoot->Mobility = EComponentMobility::Movable;
	SetRootComponent(CustomRoot);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("NodeSprite");
	SpriteComponent->SetupAttachment(CustomRoot);
}

// Called when the game starts or when spawned
void AMapNodeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapNodeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DebugDisplay();
}

void AMapNodeActor::DebugDisplay()
{
	DebugDisplayImpactRadius();
}

void AMapNodeActor::DebugDisplayImpactRadius()
{
	if (ShowImpactRadius)
	{
		FColor circleColor = FColor::Green;
		if (CheckHasNodeNearby())
		{
			circleColor = FColor::Red;
		}
		DrawDebugSphere(GetWorld(), GetActorLocation(), NodeImpactRadius, 32, circleColor);
	}
}

bool AMapNodeActor::CheckHasNodeNearby()
{
	for (TActorIterator<AMapNodeActor> It(GetWorld(), AMapNodeActor::StaticClass()); It; ++It)
	{
		if (*It == this)
		{
			continue;
		}
		
		if (FVector::Dist((*It)->GetActorLocation(),GetActorLocation()) <= NodeImpactRadius + (*It)->NodeImpactRadius)
		{
			return true;
		}
	}

	return false;
}

