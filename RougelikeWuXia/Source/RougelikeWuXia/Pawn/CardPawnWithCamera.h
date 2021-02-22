// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CardPawnWithCamera.generated.h"

class UCameraComponent;
class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UCardContainerPlaneComponent;
class UCardTriggerPlaneComponent;
class UCardBase;
class ACardActor;
class UPlayerRuntimeData;
UCLASS()
class ROUGELIKEWUXIA_API ACardPawnWithCamera : public APawn
{
	GENERATED_BODY()

public:
	enum CardPawnPhase
	{
		Browse,
		MovingCard,
		Triggering
	};

	// Sets default values for this pawn's properties
	ACardPawnWithCamera();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* MainCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* CustomRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCardContainerPlaneComponent* CardContainer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCardTriggerPlaneComponent* TriggerPlane;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DrawCard();
	void DiscardCard(ACardActor* discardingCard);
	void OnBattleBegin();

private:
	void SetCurSelectedCard(ACardActor* selectedCard);
	void SetCurFocusedCard(ACardActor* focusedCard);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* QueryPlane;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* TriggerBox;

	UPlayerRuntimeData* m_PlayerData;
	TArray<UCardBase*> m_CardsInDeck;
	TArray<UCardBase*> m_CardsInHand;
	TArray<UCardBase*> m_CardsDiscarded;
	TArray<UCardBase*> m_CardsDestroyed;
	CardPawnPhase m_CurrentPhase;
	ACardActor* m_CurFocusedCard = nullptr;
	ACardActor* m_CurSelectedCard = nullptr;

public:

	UFUNCTION(BlueprintCallable, category = "Test_Cards")
		void TestBattleBeginFired();

	UFUNCTION(BlueprintCallable, category = "Test_Cards")
		void TestCreateDeck();

	UFUNCTION(BlueprintCallable, category = "Test_Cards")
		void TestDrawNewCard();

	UFUNCTION(BlueprintImplementableEvent, category = "Test_Pawn")
		void ActorHittedUnderCursorEvent_BP(AActor* hittedActor, bool isBrowsing);
};
