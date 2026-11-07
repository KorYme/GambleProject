// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/MovementState.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachine.h"

void UMovementState::StateInit(UGenericStateMachine* InitStateMachine)
{
	Super::StateInit(InitStateMachine);
	if (UMovementStateMachine* MovementStateMachine = static_cast<UMovementStateMachine*>(InitStateMachine))
	{
		StateMachine = MovementStateMachine;
		OnStateInit(MovementStateMachine);
	}
}

void UMovementState::StateEnter(uint8 PreviousStateId)
{
	Super::StateEnter(PreviousStateId);
	OnStateEnter((EMovementStateId)PreviousStateId);
}

void UMovementState::StateExit(uint8 NextStateId)
{
	Super::StateExit(NextStateId);
	OnStateExit((EMovementStateId)NextStateId);
}
