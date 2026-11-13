// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/States/MovementStateFall.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMovementStateFall::StateEnter(EMovementStateId PreviousStateId)
{
	if (Character)
	{
		Character->GetCharacterMovement()->AirControl = GetMovementData()->FallAirControl;
		Character->GetCharacterMovement()->MaxWalkSpeed = GetMovementData()->FallMoveSpeed;
		Character->GetCharacterMovement()->GravityScale = 2 * GetMovementData()->JumpMaxHeight / ((GetMovementData()->FallDuration / 2) 
			* (GetMovementData()->FallDuration / 2) * 981);
	}
	CanCoyoteJump = PreviousStateId != EMovementStateId::Jump;
	Super::StateEnter(PreviousStateId);
}

void UMovementStateFall::StateExit(EMovementStateId NextStateId)
{
	Character->GetCharacterMovement()->GravityScale = 1;
	Super::StateExit(NextStateId);
}

void UMovementStateFall::StateTick(float DeltaTime)
{
	// TODO MC : (J'AIME PAS MAIS CA MARCHE)
	if (CanCoyoteJump && IsJumping() && StateMachine->GetCurrentStateTime() <= GetMovementData()->CoyoteJumpTimeFrame)
	{
		StateMachine->ChangeState(EMovementStateId::Jump);
	}
	if (IsOnGround())
	{
		if (IsSliding())
		{
			StateMachine->ChangeState(EMovementStateId::Slide);
			return;
		}
		StateMachine->ChangeState(EMovementStateId::Idle);
		return;
	}
	if (ChangeStateIf(EMovementStateId::Idle, IsOnGround())) return;
	MoveCharacter();
	Super::StateTick(DeltaTime);
}
