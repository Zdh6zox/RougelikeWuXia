// Fill out your copyright notice in the Description page of Project Settings.


#include "MapNodePresetConstructor.h"
#include "MapNodeActor.h"
#include "MapNodeLinkActor.h"

// Sets default values
AMapNodePresetConstructor::AMapNodePresetConstructor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapNodePresetConstructor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapNodePresetConstructor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#if WITH_EDITOR
void AMapNodePresetConstructor::ConstructFromData()
{
	RemoveCurPreset();
    const TArray<FMapNodePresetUnit>& units = PresetData.Units;
    for (const FMapNodePresetUnit& unit : units)
    {
        if (unit.NodeTemplate != NULL)
        {
            FTransform actualTrans = GetTransform() * unit.RelativeTrans;
            AMapNodeActor* nodeUnit = GetWorld()->SpawnActor<AMapNodeActor>(unit.NodeTemplate, actualTrans);
            nodeUnit->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
            if (nodeUnit != NULL)
            {
                m_CurrentNodeUnits.Add(nodeUnit);
            }
        }
    }

    for (const FMapNodePresetLink& link : PresetData.Links)
    {
        if (link.LinkTemplate != NULL)
        {
            AMapNodeLinkActor* nodeLink = GetWorld()->SpawnActor<AMapNodeLinkActor>(link.LinkTemplate, GetTransform());
            nodeLink->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
            if (nodeLink != NULL)
            {
                m_CurrentNodeLinks.Add(nodeLink);
            }
        }
    }
}

void AMapNodePresetConstructor::ImportFromDataTable()
{
	if (PresetTable == NULL)
	{
		UE_LOG(LogMain, Error, TEXT("No preset table assigned"));
		return;
	}
	TArray<FMapNodePreset*> allPresets;
	PresetTable->GetAllRows<FMapNodePreset>("", allPresets);

	if (allPresets.Num() <= CurrentDataTableRowIndex)
	{
		UE_LOG(LogMain, Error, TEXT("Preset Table Row out of index"));
		return;
	}

	PresetData = *allPresets[CurrentDataTableRowIndex];
}

void AMapNodePresetConstructor::ExportToDataTable()
{
	if (PresetTable == NULL)
	{
		UE_LOG(LogMain, Error, TEXT("No preset table assigned"));
		return;
	}
	TArray<FMapNodePreset*> allPresets;
	PresetTable->GetAllRows<FMapNodePreset>("", allPresets);

	if (allPresets.Num() > CurrentDataTableRowIndex)
	{
		*allPresets[CurrentDataTableRowIndex] = PresetData;
		return;
	}
	else if (allPresets.Num() <= CurrentDataTableRowIndex)
	{
		//add new row
		FString rowName = FString::Printf(TEXT("NewRow%d"), CurrentDataTableRowIndex);
		PresetTable->AddRow(FName(*rowName), PresetData);
	}
}

void AMapNodePresetConstructor::UpdateFromCurrent()
{
	for (int i = 0; i < m_CurrentNodeUnits.Num(); ++i)
	{
		AMapNodeActor* nodeActor = m_CurrentNodeUnits[i];
		PresetData.Units[i].RelativeTrans = GetTransform().Inverse() * nodeActor->GetTransform();
	}
}

void AMapNodePresetConstructor::RemoveCurPreset()
{
	for (int i = 0; i < m_CurrentNodeUnits.Num(); ++i)
	{
		m_CurrentNodeUnits[i]->Destroy();
	}

	for (int i = 0; i < m_CurrentNodeLinks.Num(); ++i)
	{
		m_CurrentNodeLinks[i]->Destroy();
	}

	m_CurrentNodeUnits.Empty();
	m_CurrentNodeLinks.Empty();
}
#endif

