// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ScreenOnlyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROUGELIKEWUXIA_API AScreenOnlyPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	// End PlayerController interface
};
