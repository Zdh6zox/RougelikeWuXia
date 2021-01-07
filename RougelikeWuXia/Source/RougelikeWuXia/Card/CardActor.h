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

UCLASS()
class ROUGELIKEWUXIA_API ACardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardActor();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UCardBase* Card;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UUserWidget* CardWidgetFront;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UUserWidget* CardWidgetBack;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FCardTransformData CardTransformData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TransformDuration = 2.0f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* CustomRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* CardMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	    UWidgetComponent* m_FrontWidgetComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	    UWidgetComponent* m_BackWidgetComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CardTransformTo(FCardTransformData destTrans);

	UFUNCTION(BlueprintImplementableEvent)
		void CardConstructedEvent_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void DisplayCardInfoEvent_BP();

private:
	UClass* m_FrontWidgetClass;
	UClass* m_BackWigdetClass;

	bool m_IsMoving = false;
	float m_MovingRatio = 0.f;
	FTransform m_TargetTrans;
};
