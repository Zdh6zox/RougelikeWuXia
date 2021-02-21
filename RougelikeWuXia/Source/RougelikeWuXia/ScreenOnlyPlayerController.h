// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ScreenOnlyPlayerController.generated.h"

/**
 * 
 */
class AGameManager;
UCLASS()
class ROUGELIKEWUXIA_API AScreenOnlyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	bool WasJustTriggered();
	bool WasJustReleased();

protected:
	virtual void BeginPlay() override;
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	// End PlayerController interface

private:
	AGameManager* m_GMCache;
};
