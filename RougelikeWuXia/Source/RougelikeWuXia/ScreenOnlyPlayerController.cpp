// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenOnlyPlayerController.h"
#include "Card/CardActor.h"

void AScreenOnlyPlayerController::PlayerTick(float DeltaTime)
{
	FHitResult hitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
	if (hitResult.bBlockingHit)
	{
		AActor* hittedActor = hitResult.Actor.Get();
		if (ACardActor* hittedCardActor = Cast<ACardActor>(hittedActor))
		{
			hittedCardActor->OnCardSelected();
		}
	}
}