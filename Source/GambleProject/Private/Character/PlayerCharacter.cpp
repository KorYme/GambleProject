// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "GambleProject.h"
#include "Camera/CameraComponent.h"
#include "Character/MovementStates/MovementStateMachine.h"
#include "Components/CapsuleComponent.h"
#include "Controller/GambleProjectPlayerController.h"
#include "Inputs/InputValues.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MovementStateMachine = CreateDefaultSubobject<UMovementStateMachine>(TEXT("MovementStateMachine"));
	
	// Create the Camera Component	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	// CameraComponent->SetupAttachment(GetMesh(), FName("head"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->bEnableFirstPersonFieldOfView = true;
	CameraComponent->bEnableFirstPersonScale = true;
	CameraComponent->FirstPersonFieldOfView = 90.0f;
	CameraComponent->FirstPersonScale = 0.6f;
}

void APlayerCharacter::BeginPlay()
{
	PlayerController = Cast<AGambleProjectPlayerController>(GetController());
	MovementStateMachine->Init(this, PlayerController);
	Super::BeginPlay();
}	

void APlayerCharacter::Tick(float DeltaTime)
{
	MovementStateMachine->StateMachineTick(DeltaTime);
	Super::Tick(DeltaTime);
}