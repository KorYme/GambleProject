// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/MovementState.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachine.h"

void UMovementState::StateInit(UGenericStateMachine* InitStateMachine)
{
	if (UMovementStateMachine* MovementStateMachine = static_cast<UMovementStateMachine*>(InitStateMachine))
	{
		StateMachine = MovementStateMachine;
		OnStateInit(MovementStateMachine);
	}
	Super::StateInit(InitStateMachine);
}

void UMovementState::StateEnter(uint8 PreviousStateId)
{
	OnStateEnter((EMovementStateId)PreviousStateId);
	Super::StateEnter(PreviousStateId);
}

void UMovementState::StateExit(uint8 NextStateId)
{
	OnStateExit((EMovementStateId)NextStateId);
	Super::StateExit(NextStateId);
}
