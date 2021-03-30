// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATerrainBase::ATerrainBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>("Root");
	this->SetRootComponent(DefaultRoot);

	BaseBlockMesh = CreateDefaultSubobject<UStaticMeshComponent>("BlockMesh");
	BaseBlockMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATerrainBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATerrainBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

