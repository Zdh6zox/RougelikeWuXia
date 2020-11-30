// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectComponent.generated.h"

class FEffectBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROUGELIKEWUXIA_API UEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ReceiveEffect(TSharedPtr<FEffectBase> newEffect);
	void ClearEffect() {}

	void RoundFinished(int curRoundNum);

private:
	TArray<TSharedPtr<FEffectBase>> m_CurrentEffects;
	FDelegateHandle m_RoundFinishedHandle;
};
