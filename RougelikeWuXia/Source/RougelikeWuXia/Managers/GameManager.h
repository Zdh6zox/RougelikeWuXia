// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card/CardManager.h"
#include "BattleManager.h"
#include "Card/CardEnums.h"
#include "GameManager.generated.h"

class ACharacterBase;
class UDataTable;
class ACameraActor;
class UBattleScreenWidget;
class AScreenOnlyPlayerController;
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
	FRandomStream& GetRandomStream() { return m_RandomStream; }

	FVector GetCameraUpVector();
	FVector GetCameraForwardVector();
	FRotator GetCameraRotation();

public:
	//Test Functions
	UFUNCTION(BlueprintCallable, category = "Test_Battle")
		void TestBeginBattle();

	UFUNCTION(BlueprintCallable, category = "Test_Battle")
		void TestPlayerPhaseEnd();

	UFUNCTION(BlueprintCallable, category = "Test_Battle")
		void TestPlayerAttackPhaseStart();

	UFUNCTION(BlueprintCallable, category = "Test_Battle")
		void TestPlayerAttackPhaseEnd();

	UFUNCTION(BlueprintCallable, category = "Test_Battle")
		void TestFindCardTransform(ECardLocationType locationType, int totalInhandNum, int cardIndex);

	UFUNCTION(BlueprintCallable, category = "Test_Battle")
		void TestCreateDefaultCardsInDeck(int number);

	UFUNCTION(BlueprintCallable, category = "Test_Battle")
		void TestPlayerDrawCard();

public:
    UPROPERTY(EditAnywhere, category = "Data Tables")
        UDataTable* CardDataTable;

	UPROPERTY(VisibleAnywhere, category = "Widgets")
		UBattleScreenWidget* BattleScreenWidget;

	UPROPERTY(EditAnywhere, category = "Widgets")
		TSubclassOf<UBattleScreenWidget> BattleScreenWidgetClass;

	AScreenOnlyPlayerController* GetPlayerController() { return m_PlayerController; }

private:
	FCardManager m_CardManager;
	FBattleManager m_BattleManager;

	ACameraActor* m_CameraCache;
	AScreenOnlyPlayerController* m_PlayerController;
	FRandomStream m_RandomStream;
	int32 m_CurrentRandomSeed;
};
