// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMapPawnWithCamera.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMainMapPawnWithCamera::AMainMapPawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CustomRoot = CreateDefaultSubobject<USceneComponent>("Root");
	CustomRoot->Mobility = EComponentMobility::Movable;
	SetRootComponent(CustomRoot);

	MainCameraComponent = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCameraComponent->SetupAttachment(CustomRoot);
}

// Called when the game starts or when spawned
void AMainMapPawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainMapPawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainMapPawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

