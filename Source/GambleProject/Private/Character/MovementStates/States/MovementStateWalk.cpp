// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/States/MovementStateWalk.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UMovementStateWalk::StateEnter(EMovementStateId PreviousStateId)
{
	if (ChangeForStateIf(EMovementStateId::Jump, IsJumpingWithBuffer())) return false;
	if (ChangeForStateIf(EMovementStateId::Slide, CanSlide())) return false;
	if (ChangeForStateIf(EMovementStateId::Idle, !IsMoving())) return false;
	if (ChangeForStateIf(EMovementStateId::Run, IsSprinting())) return false;
	if (ChangeForStateIf(EMovementStateId::CrouchWalk , IsCrouching())) return false;
	
	Character->GetCharacterMovement()->MaxWalkSpeed = GetMovementData()->WalkSpeed;
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	return Super::StateEnter(PreviousStateId);
}

void UMovementStateWalk::StateExit(EMovementStateId NextStateId)
{
	return Super::StateExit(NextStateId);
}

void UMovementStateWalk::StateTick(float DeltaTime)
{
	if (ChangeForStateIf(EMovementStateId::Fall, IsFalling())) return;
	if (ChangeForStateIf(EMovementStateId::Slide, CanSlide())) return;
	if (ChangeForStateIf(EMovementStateId::Idle, !IsMoving())) return;
	if (ChangeForStateIf(EMovementStateId::Run, IsSprinting())) return;
	if (ChangeForStateIf(EMovementStateId::CrouchWalk, IsCrouching())) return;
	
	MoveCharacter();
	Super::StateTick(DeltaTime);
}

EStateToggleBehaviours UMovementStateWalk::GetToggleBehaviour()
{
	return EStateToggleBehaviours::All;
}

