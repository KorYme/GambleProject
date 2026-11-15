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
	Controller->JumpInput->OnInputEvent.AddDynamic(this, &UMovementState::JumpInput);
	// Controller->SprintInput->OnInputEvent.AddDynamic(this, &UMovementState::SprintInput);
	// Controller->CrouchInput->OnInputEvent.AddDynamic(this, &UMovementState::CrouchInput);
	return true;
}

void UMovementState::StateExit(EMovementStateId NextStateId)
{
	Controller->JumpInput->OnInputEvent.RemoveDynamic(this, &UMovementState::JumpInput);
	// Controller->SprintInput->OnInputEvent.RemoveDynamic(this, &UMovementState::SprintInput);
	// Controller->CrouchInput->OnInputEvent.RemoveDynamic(this, &UMovementState::CrouchInput);
}

void UMovementState::StateEnter(uint8 PreviousStateId)
{
	if (!StateEnter((EMovementStateId)PreviousStateId))
	{
		return;
	}
	Super::StateEnter(PreviousStateId);
	OnStateEnter((EMovementStateId)PreviousStateId);
}

void UMovementState::StateExit(uint8 NextStateId)
{
	StateExit((EMovementStateId)NextStateId);
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

bool UMovementState::ChangeStateIf(EMovementStateId NewStateId, bool ShouldChangeState)
{
	if (ShouldChangeState)
	{
		StateMachine->ChangeState(NewStateId);
		return true;
	}
	return false;
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
void UMovementState::OnInputJumpTriggered(const bool IsJumping)
{
	ChangeStateIf(EMovementStateId::Jump, IsJumping);
}

void UMovementState::OnInputSprintTriggered(const bool IsSprinting)
{
	if (!IsMoving())
	{
		return;
	}
	if (IsSprinting)
	{
		StateMachine->ChangeState(EMovementStateId::Run);
	}
	else
	{
		StateMachine->ChangeState(EMovementStateId::Walk);
	}
}

void UMovementState::OnInputCrouchTriggered(const bool IsCrouching)
{
	// TODO : Add behaviour for crouch run and idle
	ChangeStateIf(EMovementStateId::CrouchIdle, IsCrouching);
}

bool UMovementState::IsMoving()
{
	return Controller->MovementInput->GetValue().SquaredLength() > 0;
}

bool UMovementState::IsOnGround()
{
	return Character->GetMovementComponent()->IsMovingOnGround();
}

bool UMovementState::IsFalling()
{
	return Character->GetMovementComponent()->IsFalling();
}

bool UMovementState::IsJumping()
{
	return Controller->JumpInput->GetValue();
}

bool UMovementState::IsJumpingWithBuffer()
{
	return Controller->JumpInput->HasBeenTriggeredSince(GetMovementData()->InputBufferTime) && Controller->JumpInput->TryConsume();
}

bool UMovementState::IsSprinting()
{
	return Controller->SprintInput->GetValue();
}

bool UMovementState::IsCrouching()
{
	return Controller->CrouchInput->GetValue();
}
	
bool UMovementState::IsSliding()
{
	float velocity = Character->GetVelocity().Length();
	float inputDir = Controller->MovementInput->GetValue().Y;
	return IsCrouching() && velocity > GetMovementData()->MinimumSpeedToSlide && inputDir > 0;
}