// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/States/MovementStateCrouchIdle.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachineData.h"

bool UMovementStateCrouchIdle::StateEnter(EMovementStateId PreviousStateId)
{
	if (ChangeForStateIf(EMovementStateId::Jump, IsJumpingWithBuffer())) return false;
	if (ChangeForStateIf(EMovementStateId::Slide, CanSlide())) return false;
	if (ChangeForStateIf(EMovementStateId::Run, IsMoving() && IsSprintingWithBuffer())) return false;
	if (ChangeForStateIf(EMovementStateId::CrouchWalk, IsMoving())) return false;

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
	if (ChangeForStateIf(EMovementStateId::Fall, IsFalling())) return;
	if (ChangeForStateIf(EMovementStateId::Idle, !IsCrouching())) return;
	if (GetMovementData()->EnableSprintToggle)
	{
		if (ChangeForStateIf(EMovementStateId::Run, IsMoving() && IsSprinting())) return;
	}
	if (ChangeForStateIf(EMovementStateId::CrouchWalk, IsMoving())) return;
	
	Super::StateTick(DeltaTime);
}

EStateToggleBehaviours UMovementStateCrouchIdle::GetToggleBehaviour()
{
	return (EStateToggleBehaviours)((uint8)EStateToggleBehaviours::CanToggleCrouch 
		| (uint8)EStateToggleBehaviours::CanToggleSprint 
		| (uint8)EStateToggleBehaviours::UntoggleSprintOnEnter);
}

