// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/MovementState.h"
#include "Camera/CameraComponent.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachine.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "Controller/GambleProjectPlayerController.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Inputs/InputValues.h"

void UMovementState::StateInit(UGenericStateMachine* InitStateMachine)
{
	StateMachine = Cast<UMovementStateMachine>(InitStateMachine);
	OnStateInit(StateMachine);
	Super::StateInit(InitStateMachine);
}

bool UMovementState::StateEnter(EMovementStateId PreviousStateId)
{
	return true;
}

void UMovementState::StateExit(EMovementStateId NextStateId)
{
}

void UMovementState::StateEnter(uint8 PreviousStateId)
{
	if (!StateEnter((EMovementStateId)PreviousStateId))
	{
		return;
	}
	Controller->JumpInput->OnInputEvent.AddDynamic(this, &UMovementState::JumpInput);
	Controller->SprintInput->OnInputEvent.AddDynamic(this, &UMovementState::SprintInput);
	Controller->CrouchInput->OnInputEvent.AddDynamic(this, &UMovementState::CrouchInput);
	
	Super::StateEnter(PreviousStateId);
	OnStateEnter((EMovementStateId)PreviousStateId);
}

void UMovementState::StateExit(uint8 NextStateId)
{
	StateExit((EMovementStateId)NextStateId);
	Controller->JumpInput->OnInputEvent.RemoveDynamic(this, &UMovementState::JumpInput);
	Controller->SprintInput->OnInputEvent.RemoveDynamic(this, &UMovementState::SprintInput);
	Controller->CrouchInput->OnInputEvent.RemoveDynamic(this, &UMovementState::CrouchInput);
	
	Super::StateExit(NextStateId);
	OnStateExit((EMovementStateId)NextStateId);
}

void UMovementState::JumpInput(const bool IsJumping)
{
	OnInputJumpTriggered(IsJumping);
}

void UMovementState::SprintInput(const bool IsSprinting)
{
	OnInputSprintTriggered(IsSprinting);
}

void UMovementState::CrouchInput(const bool IsCrouching)
{
	OnInputCrouchTriggered(IsCrouching);
}

void UMovementState::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
}

void UMovementState::MoveCharacter_Implementation()
{
	ApplyMovement();
}

void UMovementState::ApplyMovement()
{
	if (!Character) return;
	FVector2D InputMove = Controller->MovementInput->GetValue();
	FVector2D Direction2D = (FVector2D)Character->GetCameraComponent()->GetForwardVector() * InputMove.Y 
		+ (FVector2D)Character->GetCameraComponent()->GetRightVector() * InputMove.X;
	Direction2D.Normalize();
	Character->AddMovementInput(FVector(Direction2D.X, Direction2D.Y, 0.0f), 1);
}

// State change checks
bool UMovementState::IsMoving()
{
	return Controller->MovementInput->GetValue().SquaredLength() > 0;
}

bool UMovementState::ChangeStateIf(EMovementStateId NewStateId, bool ShouldChangeState)
{
	if (ShouldChangeState)
	{
		StateMachine->ChangeState(NewStateId);
		return true;
	}
	return false;
}

void UMovementState::OnInputJumpTriggered(const bool IsJumping)
{
	// TODO : Add behaviour
}

void UMovementState::OnInputSprintTriggered(const bool IsSprinting)
{
	// TODO : Add behaviour
}

void UMovementState::OnInputCrouchTriggered(const bool IsCrouching)
{
	// TODO : Add behaviour
}

bool UMovementState::IsSprinting()
{
	// TODO : Remove if possible
	return Controller->SprintInput->GetValue();
}

bool UMovementState::IsOnGround()
{
	return Character->GetMovementComponent()->IsMovingOnGround();
}

bool UMovementState::IsJumping()
{
	// TODO : Remove if possible
	return Controller->JumpInput->GetValue();
}

bool UMovementState::IsJumpingWithBuffer()
{
	return Controller->JumpInput->HasBeenTriggeredSince(GetMovementData()->InputBufferTime) && Controller->JumpInput->TryConsume();
}

bool UMovementState::IsFalling()
{
	return Character->GetMovementComponent()->IsFalling();
}

bool UMovementState::IsCrouching()
{
	// TODO : Remove if possible
	return Controller->CrouchInput->GetValue();
}
	
bool UMovementState::IsSliding()
{
	float velocity = Character->GetVelocity().Length();
	float inputDir = Controller->MovementInput->GetValue().Y;
	return IsCrouching() && velocity > GetMovementData()->MinimumSpeedToSlide && inputDir > 0;
}