// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/States/MovementStateIdle.h"
#include "Character/MovementStates/MovementState.h"
#include "Character/MovementStates/MovementStateId.h"

bool UMovementStateIdle::StateEnter(EMovementStateId PreviousStateId)
{
	if (ChangeForStateIf(EMovementStateId::Jump, IsJumpingWithBuffer())) return false;
	if (ChangeForStateIf(EMovementStateId::Slide, CanSlide())) return false;
	if (ChangeForStateIf(EMovementStateId::Run, IsMoving() && IsSprinting())) return false; 
	if (ChangeForStateIf(EMovementStateId::Walk, IsMoving())) return false;
	if (ChangeForStateIf(EMovementStateId::CrouchIdle, IsCrouching())) return false;
	
	return Super::StateEnter(PreviousStateId);
}

void UMovementStateIdle::StateExit(EMovementStateId NextStateId)
{
	Super::StateExit(NextStateId);
}

void UMovementStateIdle::StateTick(float DeltaTime)
{
	if (ChangeForStateIf(EMovementStateId::Fall, IsFalling())) return;
	if (ChangeForStateIf(EMovementStateId::Slide, CanSlide())) return;
	if (ChangeForStateIf(EMovementStateId::Run, IsMoving() && IsSprinting())) return;
	if (ChangeForStateIf(EMovementStateId::Walk, IsMoving())) return;
	if (ChangeForStateIf(EMovementStateId::CrouchIdle, IsCrouching())) return;
	
	Super::StateTick(DeltaTime);
}

EStateToggleBehaviours UMovementStateIdle::GetToggleBehaviour()
{
	return EStateToggleBehaviours::All;
}
