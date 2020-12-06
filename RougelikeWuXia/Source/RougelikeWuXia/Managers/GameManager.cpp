// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "EngineUtils.h"
#include "Character/CharacterBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AGameManager* AGameManager::GetGameManager(UWorld* world)
{
	for (TActorIterator<AGameManager> It(world, AGameManager::StaticClass()); It; ++It)
	{
		AGameManager* gameManager = *It;
		return gameManager;
	}

	return nullptr;
}


//Test Functions
void AGameManager::TestBeginBattle()
{
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterBase::StaticClass(), AllActors);

	TArray<ACharacterBase*> AllCharacters;
	for (AActor* actor : AllActors)
	{
		ACharacterBase* character = Cast<ACharacterBase>(actor);
		if (character != nullptr)
		{
			AllCharacters.Add(character);
		}
	}
	m_BattleManager.BeginBattle(AllCharacters);
}