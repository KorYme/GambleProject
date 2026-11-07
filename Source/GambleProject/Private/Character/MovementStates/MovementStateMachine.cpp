// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/MovementStateMachine.h"
#include "Character/MovementStates/MovementState.h"


void UMovementStateMachine::ChangeState(EMovementStateId NewStateId)
{
	Super::ChangeState((uint8)NewStateId);
}

TMap<uint8, TSubclassOf<UGenericState>> UMovementStateMachine::GetAllState() const
{
	TMap<uint8, TSubclassOf<UGenericState>> Map;
	for (const TPair<EMovementStateId, TSubclassOf<UMovementState>>& it : CharacterStateClasses)
	{
		Map.Emplace((uint8)it.Key, it.Value);
	}
	return Map;
}
