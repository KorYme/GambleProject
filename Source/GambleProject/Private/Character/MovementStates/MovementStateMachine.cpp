// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/MovementStateMachine.h"
#include "Character/MovementStates/MovementState.h"
#include "Engine/Engine.h"


void UMovementStateMachine::ChangeState(EMovementStateId NewStateId)
{
	Super::ChangeState((uint8)NewStateId);
}

void UMovementStateMachine::StateMachineTick(float DeltaTime)
{
	if (IsStateDebugDisplayed && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, UEnum::GetValueAsString(GetCurrentStateId()));
	}
	Super::StateMachineTick(DeltaTime);
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
