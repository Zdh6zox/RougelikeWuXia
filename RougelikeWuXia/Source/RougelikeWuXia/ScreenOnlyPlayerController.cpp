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
	Super::PlayerTick(DeltaTime);


}

bool AScreenOnlyPlayerController::WasJustTriggered()
{
	return WasInputKeyJustPressed(EKeys::LeftMouseButton);
}

bool AScreenOnlyPlayerController::WasJustReleased()
{
	return WasInputKeyJustReleased(EKeys::LeftMouseButton);
}