// Fill out your copyright notice in the Description page of Project Settings.


#include "CardTriggerPlaneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Card/CardActor.h"

// Sets default values for this component's properties
UCardTriggerPlaneComponent::UCardTriggerPlaneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCardTriggerPlaneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	m_ArrowHeadMeshComp = NewObject<UStaticMeshComponent>(GetOwner());
	GetOwner()->AddOwnedComponent(m_ArrowHeadMeshComp);
	m_ArrowHeadMeshComp->RegisterComponent(); //necessary!!
	m_ArrowHeadMeshComp->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	m_ArrowHeadMeshComp->SetStaticMesh(ArrowHeadMesh);
	m_ArrowHeadMeshComp->SetRelativeTransform(FTransform::Identity);

	for (int i = 0; i < ArrowSize; ++i)
	{
		UStaticMeshComponent* newArrowMesh = NewObject<UStaticMeshComponent>(GetOwner());
		GetOwner()->AddOwnedComponent(newArrowMesh);
		newArrowMesh->RegisterComponent(); //necessary!!
		newArrowMesh->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
		newArrowMesh->SetStaticMesh(ArrowMesh);

		newArrowMesh->SetRelativeTransform(FTransform::Identity);
		m_ArrowMeshComps.Add(newArrowMesh);
	}
}

void UCardTriggerPlaneComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//if (m_ArrowHeadMeshComp != NULL)
	//{
	//	m_ArrowHeadMeshComp->DestroyComponent();
	//}

	//m_ArrowMeshComps.Empty();
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void UCardTriggerPlaneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCardTriggerPlaneComponent::SetQueryPlane(UStaticMeshComponent* plane)
{
	m_QueryPlane = plane;
}

void UCardTriggerPlaneComponent::SetTriggerBox(UBoxComponent* triggerBox)
{
	m_TriggerBox = triggerBox;
}

bool UCardTriggerPlaneComponent::IsCardInsideBox(ACardActor* cardActor)
{
	return m_TriggerBox->IsOverlappingActor(cardActor);
}