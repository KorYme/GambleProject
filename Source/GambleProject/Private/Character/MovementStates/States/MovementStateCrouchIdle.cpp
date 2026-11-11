// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/States/MovementStateCrouchIdle.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"

void UMovementStateCrouchIdle::StateEnter(EMovementStateId PreviousStateId)
{
	if (Character)
	{
		Character->Crouch();
	}
	Super::StateEnter(PreviousStateId);
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
	Super::StateExit(NextStateId);
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
