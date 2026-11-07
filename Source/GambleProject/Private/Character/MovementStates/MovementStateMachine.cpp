// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/MovementStateMachine.h"


void UMovementStateMachine::ChangeState(EMovementStateId NewStateId)
{
	Super::ChangeState((uint8)NewStateId);
}
