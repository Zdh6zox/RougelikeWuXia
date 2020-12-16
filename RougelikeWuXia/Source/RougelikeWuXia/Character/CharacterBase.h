// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FCharacterDeadEvent, ACharacterBase*); //param: dead character
DECLARE_MULTICAST_DELEGATE_OneParam(FCharacterTurnEndEvent, ACharacterBase*); //param: turn ended character

class FEffectBase;
UCLASS()
class ROUGELIKEWUXIA_API ACharacterBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterBase();

	UPROPERTY(VisibleAnywhere, category = "Static Stats")
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, category = "Static Stats")
		float MaxStamina;

	UPROPERTY(VisibleAnywhere, category = "Runtime Stats")
		float CurrentStamina;

	UPROPERTY(VisibleAnywhere, category = "Runtime Stats")
		float CurrentHealth;

	UPROPERTY(EditAnywhere, category = "Runtime Stats")
		bool IsEnemy = false;

	bool CheckIsAlive() const;

	FCharacterDeadEvent CharacterDeadEvent_OneP;
	FCharacterTurnEndEvent CharacterTurnEnd_OneP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintImplementableEvent, category = "Test_CharacterFunc")
		void Test_TurnExecute_BP();

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

	void SendCharacterDeadEvent();
	void SendCharacterTurnEndEvent();

protected:
	FDelegateHandle m_BattleStartHandle;
	FDelegateHandle m_BattleFinishedHandle;
	FDelegateHandle m_TurnBeginHandle;
	FDelegateHandle m_TurnEndHandle;
	FDelegateHandle m_RoundStartHandle;
	FDelegateHandle m_RoundFinishedHandle;
};
