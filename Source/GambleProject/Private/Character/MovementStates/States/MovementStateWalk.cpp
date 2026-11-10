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
	if (CheckForJump()) return;
	if (CheckForFall()) return;
	if (CheckForIdle()) return;
	if (CheckForRun()) return;
	MoveCharacter();
	Super::StateTick(DeltaTime);
}