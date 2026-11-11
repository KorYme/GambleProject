// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/States/MovementStateWalk.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMovementStateWalk::StateEnter(EMovementStateId PreviousStateId)
{
	Character->GetCharacterMovement()->MaxWalkSpeed = GetMovementData()->WalkSpeed;
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	Super::StateEnter(PreviousStateId);
}

void UMovementStateWalk::StateTick(float DeltaTime)
{
	if (ChangeStateIf(EMovementStateId::Jump, IsJumping())) return;
	if (ChangeStateIf(EMovementStateId::Fall, IsFalling())) return;
	if (ChangeStateIf(EMovementStateId::CrouchWalk, IsCrouching())) return;
	if (IsMoving())
	{
		if (IsSprinting())
		{
			StateMachine->ChangeState(EMovementStateId::Run);
			return;
		}
	}
	else
	{
		StateMachine->ChangeState(EMovementStateId::Idle);
		return;
	}
	MoveCharacter();
	Super::StateTick(DeltaTime);
}