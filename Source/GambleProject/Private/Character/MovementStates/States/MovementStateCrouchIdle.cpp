// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/States/MovementStateCrouchIdle.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"

bool UMovementStateCrouchIdle::StateEnter(EMovementStateId PreviousStateId)
{
	if (ChangeStateIf(EMovementStateId::Jump, IsJumpingWithBuffer())) return false;
	
	if (Character)
	{
		Character->Crouch();
	}
	return Super::StateEnter(PreviousStateId);
}

void UMovementStateCrouchIdle::StateExit(EMovementStateId NextStateId)
{
	if (Character)
	{
		switch (NextStateId)
		{
			case EMovementStateId::CrouchIdle:
			case EMovementStateId::CrouchWalk:
			case EMovementStateId::Slide:
				break;
			default:
				Character->UnCrouch();
				break;
		}
	}
	return Super::StateExit(NextStateId);
}

void UMovementStateCrouchIdle::StateTick(float DeltaTime)
{
	if (ChangeStateIf(EMovementStateId::Jump, IsJumping())) return;
	if (ChangeStateIf(EMovementStateId::Fall, IsFalling())) return;
	if (!IsCrouching())
	{
		StateMachine->ChangeState(EMovementStateId::Idle);
		return;
	}
	else if (IsMoving())
	{
		StateMachine->ChangeState(EMovementStateId::CrouchWalk);
		return;
	}
	Super::StateTick(DeltaTime);
}
