// Fill out your copyright notice in the Description page of Project Settings.


#include "CardTriggerLine.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
ACardTriggerLine::ACardTriggerLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRoot = CreateDefaultSubobject<USceneComponent>("Root");
	CustomRoot->Mobility = EComponentMobility::Movable;
	SetRootComponent(CustomRoot);
}

// Called when the game starts or when spawned
void ACardTriggerLine::BeginPlay()
{
	Super::BeginPlay();
	
	ArrowMeshes.Empty();

	for (int i = 0; i < ArrowMeshSize; i++)
	{
		FString nameStr = FString::Printf(TEXT("Arrow Mesh %d"), i);
		UStaticMeshComponent* arrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(*nameStr);

		ArrowMeshes.Add(arrowMesh);
	}
}

// Called every frame
void ACardTriggerLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACardTriggerLine::ToggleVisibility(bool isShow)
{
	IsVisible = isShow;

	SetActorHiddenInGame(IsVisible);
}

void ACardTriggerLine::SetTriggerLinePosition(FVector startPos, FVector endPos)
{
	StartPosition = startPos;
	EndPosition = endPos;
}

void ACardTriggerLine::UpdateTriggerLine()
{
	if (!IsVisible)
	{
		return;
	}

	//Calculate all meshes location
	for (int i = 0; i < ArrowMeshes.Num(); ++i)
	{

	}
}

FVector ACardTriggerLine::CalculateLineMeshesPosition(float ratio)
{
	//B-Curve Calculation
	FVector diffVec = EndPosition - StartPosition;
	
	float controlPos_X = FVector::DotProduct(diffVec, GetActorForwardVector()) / 3.0f;
	float controlPos_Y = FVector::DotProduct(diffVec, GetActorRightVector()) / 3.0f * 4.0f;
	float controlPos_Z = FVector::DotProduct(diffVec, GetActorUpVector()) / 2.0f;
	FVector controlPos = controlPos_X * GetActorForwardVector() + controlPos_Y * GetActorRightVector() + controlPos_Z * GetActorUpVector() + StartPosition;
	FVector position = FGenericPlatformMath::Exp2(1 - ratio)* StartPosition + 2 * ratio*(1 - ratio)*controlPos + FGenericPlatformMath::Exp2(ratio) * EndPosition;

	return position;
}
