// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/States/MovementStateRun.h"
#include "Character/PlayerCharacter.h"
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
	if (CheckForJump()) return;
	if (CheckForFall()) return;
	if (CheckForIdle()) return;
	if (CheckForWalk()) return;
	MoveCharacter();
	Super::StateTick(DeltaTime);
}
