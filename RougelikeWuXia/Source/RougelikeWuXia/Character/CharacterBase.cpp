// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Effects/EffectBase.h"
#include "RougelikeWuXia.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::TurnTick(int roundNum)
{
	UE_LOG(LogMain, Log, TEXT("%s tick round %d"), *GetName(), roundNum);
}