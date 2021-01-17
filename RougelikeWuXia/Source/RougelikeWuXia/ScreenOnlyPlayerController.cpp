// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenOnlyPlayerController.h"
#include "Card/CardActor.h"
#include "Managers/GameManager.h"

void AScreenOnlyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_GMCache = AGameManager::GetGameManager(GetWorld());
}

void AScreenOnlyPlayerController::PlayerTick(float DeltaTime)
{
	FHitResult hitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
	if (hitResult.bBlockingHit)
	{
		AActor* hittedActor = hitResult.Actor.Get();
		ACardActor* hittedCardActor = Cast<ACardActor>(hittedActor);
		m_GMCache->GetCardManager().SetCurFocusedCard(hittedCardActor);
	}
}