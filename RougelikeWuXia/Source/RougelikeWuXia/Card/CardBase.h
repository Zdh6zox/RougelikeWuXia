// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardData.h"
#include "CardBase.generated.h"


class UTexture;
class UCardRuntimeData;
enum class ECardType : uint8;
/**
 * 
 */
UCLASS(BlueprintType)
class ROUGELIKEWUXIA_API UCardBase : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Card Basic")
		int CardID;

    UFUNCTION(BlueprintCallable, category = "Card Property")
        UTexture* GetCardPic() const;

    UFUNCTION(BlueprintCallable, category = "Card Property")
        FText GetCardName() const;

    UFUNCTION(BlueprintCallable, category = "Card Property")
        FText GetCardDescription() const;

	UFUNCTION(BlueprintCallable, category = "Card Property")
		ECardType GetCardType() const;

    void InitializeFromCardData(FCardData& cardData);
	void InitializeFromCardRuntimeData(UCardRuntimeData* runtimeData);

private:
	UCardRuntimeData* m_RuntimeData;
	FCardData m_CardDataCache;
};
