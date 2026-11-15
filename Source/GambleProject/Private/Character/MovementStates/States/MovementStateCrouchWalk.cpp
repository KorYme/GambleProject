// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/States/MovementStateCrouchWalk.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UMovementStateCrouchWalk::StateEnter(EMovementStateId PreviousStateId)
{
	if (ChangeStateIf(EMovementStateId::Jump, IsJumpingWithBuffer())) return false;
	
	if (Character)
	{
		Character->GetCharacterMovement()->MaxWalkSpeedCrouched = GetMovementData()->CrouchSpeed;
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		Character->Crouch();
	}
	return Super::StateEnter(PreviousStateId);
}

void UMovementStateCrouchWalk::StateExit(EMovementStateId NextStateId)
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

void UMovementStateCrouchWalk::StateTick(float DeltaTime)
{
	if (ChangeStateIf(EMovementStateId::Fall, IsFalling())) return;
	if (!IsCrouching())
	{
		StateMachine->ChangeState(EMovementStateId::Walk);
		return;
	}
	else if (!IsMoving())
	{
		StateMachine->ChangeState(EMovementStateId::CrouchIdle);
		return;
	}
	MoveCharacter();
	Super::StateTick(DeltaTime);
}