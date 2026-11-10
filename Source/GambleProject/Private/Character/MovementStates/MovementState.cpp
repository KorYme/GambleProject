// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/MovementState.h"

#include "Camera/CameraComponent.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachine.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "Character/PlayerCharacter.h"
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
	if(GEngine)
	{
		FString DisplayName = UEnum::GetValueAsString(StateMachine->GetCurrentStateId());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, DisplayName);
	}
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
	return FMath::Abs(Character->GetMoveInputDirection().SquaredLength()) > GetMovementData()->GamepadDeadZone * GetMovementData()->GamepadDeadZone;
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

bool UMovementState::CheckForIdle()
{
	if (!IsMoving())
	{
		StateMachine->ChangeState(EMovementStateId::Idle);
		return true;
	}
	return false;
}

bool UMovementState::CheckForWalk()
{
	if (IsMoving() && !Character->IsSprintInputPressed())
	{
		StateMachine->ChangeState(EMovementStateId::Walk);
		return true;
	}
	return false;
}

bool UMovementState::CheckForRun()
{
	if (IsMoving() && Character->IsSprintInputPressed())
	{
		StateMachine->ChangeState(EMovementStateId::Run);
		return true;
	}
	return false;
}

bool UMovementState::CheckForGround()
{
	if (Character && StateMachine && Character->GetMovementComponent()->IsMovingOnGround())
	{
		StateMachine->ChangeState(EMovementStateId::Idle);
		return true;
	}
	return false;
}

bool UMovementState::CheckForJump()
{
	if (Character->IsJumpInputPressed())
	{
		StateMachine->ChangeState(EMovementStateId::Jump);
		return true;
	}
	return false;
}

bool UMovementState::CheckForFall()
{
	if (Character->GetMovementComponent()->IsFalling())
	{
		StateMachine->ChangeState(EMovementStateId::Fall);
		return true;
	}
	return false;
}

bool UMovementState::CheckForLanding()
{
	if (Character->GetMovementComponent()->IsMovingOnGround())
	{
		StateMachine->ChangeState(EMovementStateId::Idle);
		return true;
	}
	return false;
}
