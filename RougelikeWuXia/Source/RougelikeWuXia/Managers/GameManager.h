// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card/CardManager.h"
#include "BattleManager.h"
#include "GameManager.generated.h"

class ACharacterBase;
UCLASS()
class ROUGELIKEWUXIA_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static AGameManager* GetGameManager(UWorld* world);

	FCardManager& GetCardManager() { return m_CardManager; }
	FBattleManager& GetBattleManager() { return m_BattleManager; }

private:
	FCardManager m_CardManager;
	FBattleManager m_BattleManager;
};
