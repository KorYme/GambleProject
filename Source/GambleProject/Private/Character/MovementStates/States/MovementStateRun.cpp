// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/States/MovementStateRun.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMovementStateRun::StateEnter(EMovementStateId PreviousStateId)
{
	Character->GetCharacterMovement()->MaxWalkSpeed = GetMovementData()->RunSpeed;
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	Super::StateEnter(PreviousStateId);
}

void UMovementStateRun::StateTick(float DeltaTime)
{
	if (ChangeStateIf(EMovementStateId::Jump, IsJumping())) return;
	if (ChangeStateIf(EMovementStateId::Fall, IsFalling())) return;
	if (ChangeStateIf(EMovementStateId::Slide, IsSliding())) return;
	if (IsMoving())
	{
		if (!IsSprinting())
		{
			StateMachine->ChangeState(EMovementStateId::Walk);
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
