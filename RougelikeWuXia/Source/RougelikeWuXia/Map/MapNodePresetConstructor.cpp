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

void AMapNodePresetConstructor::ConstructFromData()
{
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

void AMapNodePresetConstructor::ImportFromDataTable(int rowIndex)
{

}

void AMapNodePresetConstructor::ExportToDataTable()
{

}

void AMapNodePresetConstructor::CreateNewData()
{

}

