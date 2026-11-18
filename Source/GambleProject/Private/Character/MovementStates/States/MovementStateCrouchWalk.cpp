// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/States/MovementStateCrouchWalk.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UMovementStateCrouchWalk::StateEnter(EMovementStateId PreviousStateId)
{
	if (ChangeForStateIf(EMovementStateId::Jump, IsJumpingWithBuffer())) return false;
	if (ChangeForStateIf(EMovementStateId::Slide, CanSlide())) return false;
	if (ChangeForStateIf(EMovementStateId::Run, IsMoving() && IsSprinting())) return false;
	if (ChangeForStateIf(EMovementStateId::CrouchIdle, !IsMoving())) return false;
	
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
	if (ChangeForStateIf(EMovementStateId::Fall, IsFalling())) return;
	if (ChangeForStateIf(EMovementStateId::Slide, CanSlide())) return;
	if (GetMovementData()->EnableSprintToggle)
	{
		if (ChangeForStateIf(EMovementStateId::Run, IsMoving() && IsSprinting())) return;
	}
	if (ChangeForStateIf(EMovementStateId::CrouchIdle, !IsMoving())) return;
	if (ChangeForStateIf(EMovementStateId::Walk, !IsCrouching())) return;
	
	MoveCharacter(DeltaTime);
	Super::StateTick(DeltaTime);
}

EStateToggleBehaviours UMovementStateCrouchWalk::GetToggleBehaviour()
{
	return (EStateToggleBehaviours)((uint8)EStateToggleBehaviours::CanToggleCrouch 
		| (uint8)EStateToggleBehaviours::CanToggleSprint 
		| (uint8)EStateToggleBehaviours::UntoggleSprintOnEnter);
}
