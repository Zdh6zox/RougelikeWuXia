// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ROUGELIKEWUXIA_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, category = "Deck")
        TArray<uint32> CardDeck;

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OnPlayerSetupBegin();
	void OnPlayerSetupEnd();

private:
	FDelegateHandle m_PlayerSetupStartHandle;
	FDelegateHandle m_PlayerSetupFinishedHandle;
};
