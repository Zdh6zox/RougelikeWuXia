// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "EngineUtils.h"
#include "Character/CharacterBase.h"
#include "Engine/DataTable.h" 
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "ScreenOnlyPlayerController.h"
#include "Pawn/CardPawnWithCamera.h"
#include "UI/BattleScreenWidget.h"
#include "Card/CardActor.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	m_BattleManager.Initialize(this);
	m_CardManager.InitializeManager(this);
	m_MapManager.Initialize(this);

	m_RandomStream.GenerateNewSeed();
	m_CurrentRandomSeed = m_RandomStream.GetCurrentSeed();

	Super::BeginPlay();

	AScreenOnlyPlayerController* playerCon = Cast<AScreenOnlyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(playerCon);
	m_PlayerController = playerCon;

	if (BattleScreenWidgetClass != NULL)
	{
		BattleScreenWidget = CreateWidget<UBattleScreenWidget>(m_PlayerController, BattleScreenWidgetClass);
		check(BattleScreenWidget);

		BattleScreenWidget->AddToViewport(1);
	}
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	m_BattleManager.UpdateBattle();
	//m_CardManager.UpdateCards();

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

FVector AGameManager::GetCameraUpVector()
{
	if (m_CameraCache != nullptr)
	{
		return m_CameraCache->GetActorUpVector();
	}
	else
	{
		for (TActorIterator<ACameraActor> It(GetWorld(), ACameraActor::StaticClass()); It; ++It)
		{
			m_CameraCache = *It;
			break;
		}

		return m_CameraCache->GetActorUpVector();
	}
}

FVector AGameManager::GetCameraForwardVector()
{
	if (m_CameraCache != nullptr)
	{
		return m_CameraCache->GetActorForwardVector();
	}
	else
	{
		for (TActorIterator<ACameraActor> It(GetWorld(), ACameraActor::StaticClass()); It; ++It)
		{
			m_CameraCache = *It;
			break;
		}

		return m_CameraCache->GetActorForwardVector();
	}
}

FRotator AGameManager::GetCameraRotation()
{
	if (m_CameraCache != nullptr)
	{
		return m_CameraCache->GetActorRotation();
	}
	else
	{
		for (TActorIterator<ACameraActor> It(GetWorld(), ACameraActor::StaticClass()); It; ++It)
		{
			m_CameraCache = *It;
			break;
		}

		return m_CameraCache->GetActorRotation();
	}
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

void AGameManager::TestPlayerAttackPhaseStart()
{
	m_BattleManager.EnterSolo(nullptr);
}

void AGameManager::TestPlayerAttackPhaseEnd()
{
	m_BattleManager.ExitSolo();
}

void AGameManager::TestPlayerPhaseEnd()
{
	m_BattleManager.ExitPlayerPhase();
}

void AGameManager::TestFindCardTransform(ECardLocationType locationType, int totalInhandNum, int cardIndex)
{
	if (locationType!= ECardLocationType::InHand)
	{
		m_CardManager.GetTransformData(locationType);
	}
	else
	{
		m_CardManager.GetInHandTransformData(totalInhandNum, cardIndex);
	}
}

void AGameManager::TestCreateDefaultCardsInDeck(int number)
{
	ACardPawnWithCamera* pawn = Cast<ACardPawnWithCamera>(GetPlayerController()->GetPawn());

	pawn->TestCreateDeck();
	//m_CardManager.Test_CreateDefaultCardsInDeck(number);
}

void AGameManager::TestPlayerDrawCard()
{
	ACardPawnWithCamera* pawn = Cast<ACardPawnWithCamera>(GetPlayerController()->GetPawn());

	pawn->DrawCard();
	//m_CardManager.PlayerDrawCard();
}