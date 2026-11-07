// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "GambleProject.h"
#include "Character/PlayerInputData.h"
#include "Character/MovementStates/MovementStateMachine.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MovementStateMachine = CreateDefaultSubobject<UMovementStateMachine>(TEXT("MovementStateMachine"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovementStateMachine->StateMachineTick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputData->MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnInputMove);

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
}

void APlayerCharacter::OnInputMove(const FInputActionValue& InputActionValue)
{
	CurrentMoveInput = InputActionValue.Get<FVector2D>();
	OnMoveInputEvent.Broadcast(CurrentMoveInput);
}

void APlayerCharacter::OnInputAim(const FInputActionValue& InputActionValue)
{
	CurrentAimInput = InputActionValue.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(CurrentAimInput.X);
		AddControllerPitchInput(CurrentAimInput.Y);
	}
	OnAimInputEvent.Broadcast(CurrentAimInput);
}

void APlayerCharacter::OnInputJump(const FInputActionValue& InputActionValue)
{
	CurrentJumpInput = InputActionValue.Get<bool>();
	OnJumpInputEvent.Broadcast(CurrentJumpInput);
}

void APlayerCharacter::OnInputSprint(const FInputActionValue& InputActionValue)
{
	CurrentSprintInput = InputActionValue.Get<bool>();
	OnSprintInputEvent.Broadcast(CurrentSprintInput);
}

void APlayerCharacter::OnInputCrouch(const FInputActionValue& InputActionValue)
{
	CurrentCrouchInput = InputActionValue.Get<bool>();
	OnCrouchInputEvent.Broadcast(CurrentCrouchInput);
}

void APlayerCharacter::OnInputFire(const FInputActionValue& InputActionValue)
{
	CurrentFireInput = InputActionValue.Get<bool>();
	OnFireInputEvent.Broadcast(CurrentFireInput);
}

void APlayerCharacter::OnInputReroll(const FInputActionValue& InputActionValue)
{
	CurrentRerollInput = InputActionValue.Get<bool>();
	OnRerollInputEvent.Broadcast(CurrentRerollInput);
}
