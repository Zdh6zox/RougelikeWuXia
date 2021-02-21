// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerLineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values for this component's properties
UTriggerLineComponent::UTriggerLineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerLineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ArrowMeshes.Empty();

	for (int i = 0; i < ArrowMeshSize; i++)
	{
		FString nameStr = FString::Printf(TEXT("Arrow Mesh %d"), i);
		UStaticMeshComponent* arrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(*nameStr);

		ArrowMeshes.Add(arrowMesh);
	}
}


// Called every frame
void UTriggerLineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (!IsTriggerLineVisible)
	{
		return;
	}

	//Calculate all meshes location
	for (int i = 0; i < ArrowMeshes.Num(); ++i)
	{

	}
}

void UTriggerLineComponent::ToggleVisibility(bool isShow)
{
	IsTriggerLineVisible = isShow;
}

void UTriggerLineComponent::SetTriggerLinePosition(FVector startPos, FVector endPos)
{
	StartPosition = startPos;
	EndPosition = endPos;
}

FVector UTriggerLineComponent::CalculateLineMeshesPosition(float ratio)
{
	//B-Curve Calculation, use relative location
	FVector diffVec = EndPosition - StartPosition;

	
	//float controlPos_X = FVector::DotProduct(diffVec, GetRelativeTransform()->) / 3.0f;
	//float controlPos_Y = FVector::DotProduct(diffVec, GetActorRightVector()) / 3.0f * 4.0f;
	//float controlPos_Z = FVector::DotProduct(diffVec, GetActorUpVector()) / 2.0f;
	//FVector controlPos = controlPos_X * GetActorForwardVector() + controlPos_Y * GetActorRightVector() + controlPos_Z * GetActorUpVector() + StartPosition;

	float controlPos_X = (EndPosition - StartPosition).X / 3.0f;
	float controlPos_Y = (EndPosition - StartPosition).Y / 3.0f * 4.0f;
	//float controlPos_Z = (EndPosition - StartPosition).Z / 2.0f;
	FVector controlPos = FVector(controlPos_X, controlPos_Y, 0.0f);
	FVector position = FGenericPlatformMath::Exp2(1 - ratio)* StartPosition + 2 * ratio*(1 - ratio)*controlPos + FGenericPlatformMath::Exp2(ratio) * EndPosition;

	return position;
}

