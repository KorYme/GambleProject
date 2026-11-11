// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/States/MovementStateJump.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMovementStateJump::StateEnter(EMovementStateId PreviousStateId)
{
	if (Character)
	{
		Character->GetCharacterMovement()->AirControl = GetMovementData()->JumpAirControl;
		Character->GetCharacterMovement()->MaxWalkSpeed = GetMovementData()->JumpMoveSpeed;
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		Character->GetCharacterMovement()->JumpZVelocity = 4 * GetMovementData()->JumpMaxHeight / GetMovementData()->JumpDuration;
		Character->GetCharacterMovement()->GravityScale = 2 * GetMovementData()->JumpMaxHeight / ((GetMovementData()->JumpDuration / 2) 
			* (GetMovementData()->JumpDuration / 2) * 981);
		JumpTimer = GetMovementData()->JumpDuration / 2;
		Character->Jump();
	}
	Super::StateEnter(PreviousStateId);
}

void UMovementStateJump::StateExit(EMovementStateId NextStateId)
{
	Character->StopJumping();
	Character->GetCharacterMovement()->GravityScale = 1.f;
	Super::StateExit(NextStateId);
}

void UMovementStateJump::StateTick(float DeltaTime)
{
	if (ChangeStateIf(EMovementStateId::Idle, IsOnGround())) return;
	JumpTimer -= DeltaTime;
	if (Character->GetCharacterMovement()->Velocity.Z < 0.f)
	{
		Character->StopJumping();
		StateMachine->ChangeState(EMovementStateId::Fall);
		return;
	}
	MoveCharacter();
	Super::StateTick(DeltaTime);
}
