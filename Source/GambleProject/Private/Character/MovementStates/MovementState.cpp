// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/MovementState.h"

#include "Camera/CameraComponent.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachine.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/PawnMovementComponent.h"

void UMovementState::StateInit(UGenericStateMachine* InitStateMachine)
{
	if (UMovementStateMachine* MovementStateMachine = static_cast<UMovementStateMachine*>(InitStateMachine))
	{
		StateMachine = MovementStateMachine;
		OnStateInit(MovementStateMachine);
	}
	Super::StateInit(InitStateMachine);
}

void UMovementState::StateEnter(EMovementStateId PreviousStateId)
{
}

void UMovementState::StateExit(EMovementStateId NextStateId)
{
}

void UMovementState::StateEnter(uint8 PreviousStateId)
{
	StateEnter((EMovementStateId)PreviousStateId);
	Super::StateEnter(PreviousStateId);
	OnStateEnter((EMovementStateId)PreviousStateId);
}

void UMovementState::StateExit(uint8 NextStateId)
{
	StateExit((EMovementStateId)NextStateId);
	Super::StateExit(NextStateId);
	OnStateExit((EMovementStateId)NextStateId);
}

void UMovementState::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
}

// State change checks
bool UMovementState::IsMoving()
{
	return Character->GetMoveInputDirection().SquaredLength() > 0;
}

void UMovementState::MoveCharacter_Implementation()
{
	ApplyMovement();
}

void UMovementState::ApplyMovement()
{
	if (!Character) return;
	FVector2D InputMove = Character->GetMoveInputDirection();
	FVector2D Direction2D = (FVector2D)Character->GetCameraComponent()->GetForwardVector() * InputMove.Y 
		+ (FVector2D)Character->GetCameraComponent()->GetRightVector() * InputMove.X;
	Direction2D.Normalize();
	FVector Direction(Direction2D.X, Direction2D.Y, 0.0f);
	Character->AddMovementInput(Direction, 1);
}

bool UMovementState::IsSprinting()
{
	return Character->IsSprintInputPressed();
}

bool UMovementState::IsOnGround()
{
	return Character->GetMovementComponent()->IsMovingOnGround();
}

bool UMovementState::IsJumping()
{
	return Character->IsJumpInputPressed();
}

bool UMovementState::IsFalling()
{
	return Character->GetMovementComponent()->IsFalling();
}

bool UMovementState::IsCrouching()
{
	return Character->IsCrouchInputPressed();
}

bool UMovementState::IsSliding()
{
	float velocity = Character->GetVelocity().Length();
	float inputDir = Character->GetMoveInputDirection().Y;
	return IsCrouching() && velocity > GetMovementData()->MinimumSpeedToSlide && inputDir > 0;
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
