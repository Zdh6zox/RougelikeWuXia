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
	UPROPERTY(EditAnywhere, category = "Attributes")
		int Strength;

	UPROPERTY(EditAnywhere, category = "Attributes")
		int Agility;

	UPROPERTY(EditAnywhere, category = "Attributes")
		int InnerStrength;

	UPROPERTY(EditAnywhere, category = "Attributes")
		int Intelligence;

	UPROPERTY(EditAnywhere, category = "Attributes")
		int Instinct;

	UPROPERTY(EditAnywhere, category = "Attributes")
		int Luckiness;
};
