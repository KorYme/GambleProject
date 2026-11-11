// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/MovementStateMachine.h"
#include "Character/MovementStates/MovementState.h"


void UMovementStateMachine::ChangeState(EMovementStateId NewStateId)
{
	EMovementStateId OldStateId = GetCurrentStateId();
	Super::ChangeState((uint8)NewStateId);
	if (IsStateDebugDisplayed && GEngine && GetCurrentStateId() != OldStateId)
	{
		FString DisplayName = UEnum::GetValueAsString(GetCurrentStateId());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, DisplayName);
	}
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
