// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterBase.generated.h"

class FEffectBase;
UCLASS()
class ROUGELIKEWUXIA_API ACharacterBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterBase();

	UPROPERTY(VisibleAnywhere, category = "Static Stats")
		float MaxHealth;

	UPROPERTY(VisibleAnywhere, category = "Static Stats")
		float MaxStamina;

	UPROPERTY(VisibleAnywhere, category = "Runtime Stats")
		float CurrentStamina;

	UPROPERTY(VisibleAnywhere, category = "Runtime Stats")
		float CurrentHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnBattleStart(const TArray<ACharacterBase*> participants);
	virtual void OnBattleFinished(const TArray<ACharacterBase*> participants);
	virtual void OnTurnBegin(ACharacterBase* turnOwner);
	virtual void OnTurnEnd(ACharacterBase* turnOwner);
	virtual void OnRoundStart(int roundNum);
	virtual void OnRoundFinished(int roundNum);
	virtual void ForceEndTurn(/*EndReason*/) {}

protected:
	FDelegateHandle m_BattleStartHandle;
	FDelegateHandle m_BattleFinishedHandle;
	FDelegateHandle m_TurnBeginHandle;
	FDelegateHandle m_TurnEndHandle;
	FDelegateHandle m_RoundStartHandle;
	FDelegateHandle m_RoundFinishedHandle;
};
