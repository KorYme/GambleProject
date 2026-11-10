// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/States/MovementStateFall.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMovementStateFall::StateEnter(EMovementStateId PreviousStateId)
{
	if (Character)
	{
		Character->GetCharacterMovement()->AirControl = GetMovementData()->FallAirControl;
		Character->GetCharacterMovement()->GravityScale *= GetMovementData()->FallGravityScale;
		Character->GetCharacterMovement()->MaxWalkSpeed = GetMovementData()->FallHorizontalMoveSpeed;
	}
	Super::StateEnter(PreviousStateId);
}

void UMovementStateFall::StateExit(EMovementStateId NextStateId)
{
	Character->GetCharacterMovement()->GravityScale = 1;
	Super::StateExit(NextStateId);
}

void UMovementStateFall::StateTick(float DeltaTime)
{
	if (CheckForGround()) return;
	MoveCharacter();
	Super::StateTick(DeltaTime);
}
