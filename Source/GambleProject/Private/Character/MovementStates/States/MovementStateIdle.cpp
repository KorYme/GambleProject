// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/States/MovementStateIdle.h"
#include "Character/MovementStates/MovementState.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Controller/GambleProjectPlayerController.h"

bool UMovementStateIdle::StateEnter(EMovementStateId PreviousStateId)
{
	if (ChangeStateIf(EMovementStateId::Jump, IsJumpingWithBuffer())) return false;
	
	return Super::StateEnter(PreviousStateId);
}

void UMovementStateIdle::StateExit(EMovementStateId NextStateId)
{
	Super::StateExit(NextStateId);
}

void UMovementStateIdle::StateTick(float DeltaTime)
{
	if (ChangeStateIf(EMovementStateId::Fall, IsFalling())) return;
	if (ChangeStateIf(EMovementStateId::CrouchIdle, IsCrouching())) return;
	if (IsMoving())
	{
		if (!IsSprinting())
		{
			StateMachine->ChangeState(EMovementStateId::Walk);
		}
		else
		{
			StateMachine->ChangeState(EMovementStateId::Run);
		}
		return;
	}
	Super::StateTick(DeltaTime);
}
