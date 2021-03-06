// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardTransformData.h"
#include "CardActor.generated.h"

class UCardBase;
class UUserWidget;
class UStaticMeshComponent;
class UWidgetComponent;
class ACardActor;
class UBoxComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FCardFocusedEvent, ACardActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FCardLostFocusEvent, ACardActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FCardSelectedEvent, ACardActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FCardUnselectedEvent, ACardActor*);
//DECLARE_MULTICAST_DELEGATE_OneParam(FCardAboutToTriggerEvent, ACardActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FCardCancelTriggerEvent, ACardActor*);
//DECLARE_MULTICAST_DELEGATE_OneParam(FCardTriggeredEvent, ACardActor*);

UCLASS()
class ROUGELIKEWUXIA_API ACardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardActor();
	~ACardActor();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UCardBase* Card;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UUserWidget* CardWidgetFront;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UUserWidget* CardWidgetBack;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FCardTransformData CardTransformData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float InHandTransDuration = 2.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DisplayTransDuration = 0.5f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool IsFocused = false;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool IsSelected = false;

	FCardFocusedEvent CardFocusedEvent_OneP;
	FCardLostFocusEvent CardLostFocusEvent_OneP;
	FCardSelectedEvent CardSelectedEvent_OneP;
	FCardUnselectedEvent CardUnselectedEvent_OneP;
	//FCardAboutToTriggerEvent CardAboutToTriggerEvent_OneP;
	FCardCancelTriggerEvent CardCancelTriggerEvent_OneP;
	//FCardTriggeredEvent CardTriggeredEvent_OneP;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* CustomRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* CardMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	    UWidgetComponent* FrontWidgetComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	    UWidgetComponent* BackWidgetComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* CardBox;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CardTransformTo(FCardTransformData destTrans);

	void OnCardFocused();
	void OnCardLostFocus();
	void OnCardSelected();
	void OnCardUnselected();
	void OnCardTriggered();

	UFUNCTION(BlueprintImplementableEvent)
		void CardFocusedEvent_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void CardLostFocusEvent_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void CardSelectedEvent_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void CardUnselectedEvent_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void CardDiscardedEvent_BP();

private:
	void StartMovingTo(FTransform targetTrans, float time);
	void StopMoving();

	UClass* m_FrontWidgetClass;
	UClass* m_BackWigdetClass;

	bool m_IsMoving = false;
	bool m_IsDiscarding = false;
	float m_MovingRatio = 0.f;
	float m_CurTransDuration = 0.f;
	FTransform m_OriginTrans;
	FTransform m_TargetTrans;
};
