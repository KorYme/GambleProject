// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/MovementState.h"

void UMovementState::StateInit(UMovementStateMachine* InitStateMachine)
{
	OnStateInit(InitStateMachine);
}

void UMovementState::StateEnter(EMovementStateId PreviousStateId)
{
	OnStateEnter(PreviousStateId);
}

void UMovementState::StateExit(EMovementStateId NextStateId)
{
	OnStateExit(NextStateId);
}

void UMovementState::StateTick(float DeltaTime)
{
	OnStateTick(DeltaTime);
}
