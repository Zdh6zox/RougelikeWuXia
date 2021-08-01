// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMapActor.h"

// Sets default values
AMainMapActor::AMainMapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainMapActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainMapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainMapActor::ConstructMap()
{
	MapData = m_MapConstructor.ConstructMap(MapConstructData);
}

void AMainMapActor::LoadConstructedMap()
{

}

