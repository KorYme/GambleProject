// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "GambleProject.h"
#include "Camera/CameraComponent.h"
#include "Inputs/PlayerInputData.h"
#include "Character/MovementStates/MovementStateMachine.h"
#include "Components/CapsuleComponent.h"
#include "Inputs/InputValues.h"


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
	InputValuesInit();
	MovementStateMachine->Init(this);
	Super::BeginPlay();
}	

void APlayerCharacter::Tick(float DeltaTime)
{
	MovementStateMachine->StateMachineTick(DeltaTime);
	InputValuesTick(DeltaTime);
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputData->MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnInputMove);
		EnhancedInputComponent->BindAction(InputData->MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnInputMove);
 
		EnhancedInputComponent->BindAction(InputData->MouseAimAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnInputAim);
		EnhancedInputComponent->BindAction(InputData->GamepadAimAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnInputAim);
		
		EnhancedInputComponent->BindAction(InputData->JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::OnInputJump);
		EnhancedInputComponent->BindAction(InputData->JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnInputJump);
		
		EnhancedInputComponent->BindAction(InputData->SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::OnInputSprint);
		EnhancedInputComponent->BindAction(InputData->SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnInputSprint);
		
		EnhancedInputComponent->BindAction(InputData->CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::OnInputCrouch);
		EnhancedInputComponent->BindAction(InputData->CrouchAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnInputCrouch);

		EnhancedInputComponent->BindAction(InputData->FireAction, ETriggerEvent::Started, this, &APlayerCharacter::OnInputFire);
		EnhancedInputComponent->BindAction(InputData->FireAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnInputFire);
		
		EnhancedInputComponent->BindAction(InputData->RerollAction, ETriggerEvent::Started, this, &APlayerCharacter::OnInputReroll);
		EnhancedInputComponent->BindAction(InputData->RerollAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnInputReroll);
	}
	else
	{
		UE_LOG(LogGambleProject, Error, TEXT("'%s' Failed to find an Enhanced Input Component!"), *GetNameSafe(this));
	}
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::InputValuesInit()
{
	MovementInput = NewObject<UInputVectorValue>();
	AimInput = NewObject<UInputVectorValue>();
	JumpInput = NewObject<UInputBoolValue>();
	SprintInput = NewObject<UInputBoolValue>();
	CrouchInput = NewObject<UInputBoolValue>();
	FireInput = NewObject<UInputBoolValue>();
	RerollInput = NewObject<UInputBoolValue>();
}

void APlayerCharacter::InputValuesTick(float DeltaTime)
{
	MovementInput->Tick(DeltaTime);
	AimInput->Tick(DeltaTime);
	JumpInput->Tick(DeltaTime);
	SprintInput->Tick(DeltaTime);
	CrouchInput->Tick(DeltaTime);
	FireInput->Tick(DeltaTime);
	RerollInput->Tick(DeltaTime);
}

void APlayerCharacter::OnInputMove(const FInputActionValue& InputActionValue)
{
	MovementInput->SetValue(InputActionValue.Get<FVector2D>());
}

void APlayerCharacter::OnInputAim(const FInputActionValue& InputActionValue)
{
	if (GetController())
	{
		AddControllerYawInput(AimInput->GetValue().X);
		AddControllerPitchInput(AimInput->GetValue().Y);
	}
	AimInput->SetValue(InputActionValue.Get<FVector2D>());
}

void APlayerCharacter::OnInputJump(const FInputActionValue& InputActionValue)
{
	JumpInput->SetValue(InputActionValue.Get<bool>());
}

void APlayerCharacter::OnInputSprint(const FInputActionValue& InputActionValue)
{
	SprintInput->SetValue(InputActionValue.Get<bool>());
}

void APlayerCharacter::OnInputCrouch(const FInputActionValue& InputActionValue)
{
	CrouchInput->SetValue(InputActionValue.Get<bool>());
}

void APlayerCharacter::OnInputFire(const FInputActionValue& InputActionValue)
{
	FireInput->SetValue(InputActionValue.Get<bool>());
}

void APlayerCharacter::OnInputReroll(const FInputActionValue& InputActionValue)
{
	RerollInput->SetValue(InputActionValue.Get<bool>());
}
