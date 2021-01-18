// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenOnlyPlayerController.h"
#include "Card/CardActor.h"
#include "Managers/GameManager.h"
#include "GameFramework/PlayerInput.h"

void AScreenOnlyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_GMCache = AGameManager::GetGameManager(GetWorld());
}

void AScreenOnlyPlayerController::PlayerTick(float DeltaTime)
{
	bool justPressed = false;
	if (PlayerInput->WasJustPressed(EKeys::LeftMouseButton))
	{
		justPressed = true;
	}

	bool justReleased = false;
	if (PlayerInput->WasJustReleased(EKeys::LeftMouseButton))
	{
		justReleased = true;
	}

	FHitResult hitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
	if (hitResult.bBlockingHit)
	{
		AActor* hittedActor = hitResult.Actor.Get();
		ACardActor* hittedCardActor = Cast<ACardActor>(hittedActor);
		m_GMCache->GetCardManager().SetCurFocusedCard(hittedCardActor);

		if (justPressed)
		{
			m_GMCache->GetCardManager().SetCurSelectedCard(hittedCardActor);
		}
	}
}