// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/States/MovementStateRun.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UMovementStateRun::StateEnter(EMovementStateId PreviousStateId)
{
	if (ChangeForStateIf(EMovementStateId::Jump, IsJumpingWithBuffer())) return false;
	if (ChangeForStateIf(EMovementStateId::Slide, CanSlide() && IsCrouchingWithBuffer())) return false;
	if (ChangeForStateIf(EMovementStateId::Walk, !IsSprintingWithBuffer())) return false;
	
	Character->GetCharacterMovement()->MaxWalkSpeed = GetMovementData()->RunSpeed;
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	return Super::StateEnter(PreviousStateId);
}

void UMovementStateRun::StateExit(EMovementStateId NextStateId)
{
	return Super::StateExit(NextStateId);
}

void UMovementStateRun::StateTick(float DeltaTime)
{
	if (ChangeForStateIf(EMovementStateId::Fall, IsFalling())) return;
	if (ChangeForStateIf(EMovementStateId::Slide, CanSlide() && IsCrouching())) return;
	if (ChangeForStateIf(EMovementStateId::Idle, !IsMoving())) return;
	if (ChangeForStateIf(EMovementStateId::Walk, !IsSprinting())) return;
	if (ChangeForStateIf(EMovementStateId::CrouchWalk, IsCrouching())) return;
	
	MoveCharacter();
	Super::StateTick(DeltaTime);
}

EStateToggleBehaviours UMovementStateRun::GetToggleBehaviour()
{
	return (EStateToggleBehaviours)((uint8)EStateToggleBehaviours::CanToggleCrouch 
		| (uint8)EStateToggleBehaviours::CanToggleSprint 
		| (uint8)EStateToggleBehaviours::UntoggleCrouchOnEnter);
}
