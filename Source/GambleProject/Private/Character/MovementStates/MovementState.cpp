// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/MovementState.h"

#include "Camera/CameraComponent.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachine.h"
#include "Character/PlayerCharacter.h"
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
	if (((uint8)GetToggleBehaviour() & (uint8)EStateToggleBehaviours::UntoggleSprintOnEnter) != 0)
	{
		UntoggleSprint();
	}
	if (((uint8)GetToggleBehaviour() & (uint8)EStateToggleBehaviours::UntoggleCrouchOnEnter) != 0)
	{
		UntoggleCrouch();
	}
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

bool UMovementState::ChangeForStateIf(EMovementStateId NewStateId, bool ShouldChangeState)
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
	ChangeForStateIf(EMovementStateId::Jump, IsJumping);
}

bool UMovementState::IsMoving()
{
	return StateMachine->IsMoving();
}

bool UMovementState::IsOnGround()
{
	return StateMachine->IsOnGround();
}

bool UMovementState::IsFalling()
{
	return StateMachine->IsFalling();
}

bool UMovementState::IsJumping()
{
	return StateMachine->IsJumping();
}

bool UMovementState::IsJumpingWithBuffer()
{
	return StateMachine->IsJumpingWithBuffer();
}

bool UMovementState::IsSprinting()
{
	return StateMachine->IsSprinting();
}

bool UMovementState::IsSprintingWithBuffer()
{
	return StateMachine->IsSprintingWithBuffer();
}

void UMovementState::UntoggleSprint()
{
	StateMachine->UntoggleSprint();
}

bool UMovementState::IsCrouching()
{
	return StateMachine->IsCrouching();
}

bool UMovementState::IsCrouchingWithBuffer()
{
	return StateMachine->IsCrouchingWithBuffer();
}

void UMovementState::UntoggleCrouch()
{
	StateMachine->UntoggleCrouch();
}

bool UMovementState::CanSlide()
{
	return StateMachine->CanSlide();
}
