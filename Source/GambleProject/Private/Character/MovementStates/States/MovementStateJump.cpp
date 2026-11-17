// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/States/MovementStateJump.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UMovementStateJump::StateEnter(EMovementStateId PreviousStateId)
{
	if (Character)
	{
		Character->GetCharacterMovement()->AirControl = GetMovementData()->JumpAirControl;
		Character->GetCharacterMovement()->MaxWalkSpeed = GetMovementData()->JumpMoveSpeed;
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		JumpTimer = GetMovementData()->JumpDuration / 2;
		Character->GetCharacterMovement()->JumpZVelocity = 4 * GetMovementData()->JumpMaxHeight / GetMovementData()->JumpDuration;
		Character->GetCharacterMovement()->GravityScale = 2 * GetMovementData()->JumpMaxHeight / (JumpTimer * JumpTimer * 981);
		Character->Jump();
	}
	return Super::StateEnter(PreviousStateId);
}

void UMovementStateJump::StateExit(EMovementStateId NextStateId)
{
	Character->StopJumping();
	Character->GetCharacterMovement()->GravityScale = 1.f;
	return Super::StateExit(NextStateId);
}

void UMovementStateJump::StateTick(float DeltaTime)
{
	if (ChangeForStateIf(EMovementStateId::Idle, IsOnGround())) return;
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

EStateToggleBehaviours UMovementStateJump::GetToggleBehaviour()
{
	return EStateToggleBehaviours::UntoggleCrouchOnEnter;
}


void UMovementStateJump::OnInputJumpTriggered(const bool IsJumping)
{
}
