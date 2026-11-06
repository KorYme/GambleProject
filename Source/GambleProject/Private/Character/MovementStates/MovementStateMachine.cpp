// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/MovementStateMachine.h"
#include "Character/MovementStates/MovementState.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/PlayerCharacter.h"

void UMovementStateMachine::Init(APlayerCharacter* InCharacter)
{
	this->Character = InCharacter;
	GetStates();
	InitStates();
}

void UMovementStateMachine::Tick(float DeltaTime)
{
	if (CurrentState)
	{
		CurrentState->StateTick(DeltaTime);
	}
}

void UMovementStateMachine::ChangeState(EMovementStateId NextStateId)
{
	if (NextStateId == CurrentStateId) return;
	
	UMovementState** NextState = AllStates.Find(NextStateId);

	// Do nothing if no state is linked to nextStateId
	if (!NextState)
	{
		UE_LOG(LogTemp, Log, TEXT("No state found with id : %s"), *UEnum::GetValueAsString(NextStateId));
		return;
	}

	if (CurrentState)
	{
		CurrentState->StateExit(NextStateId);
	}

	EMovementStateId PreviousStateID = CurrentStateId;
	CurrentStateId = NextStateId;
	CurrentState = *NextState;

	CurrentState->StateEnter(PreviousStateID);
}

void UMovementStateMachine::GetStates()
{
	// const USmashCharacterSettings* CharacterSettings = GetDefault<USmashCharacterSettings>();
	// for (TTuple<ESmashCharacterStateID, TSubclassOf<USmashCharacterState>> KvpOverridedState : Character->GetOverridedStatesMap())
	// {
	// 	AllStates.Emplace(KvpOverridedState.Key, NewObject<USmashCharacterState>(this, KvpOverridedState.Value));
	// }
	// for (TTuple<ESmashCharacterStateID, TSubclassOf<USmashCharacterState>> KvpState : CharacterSettings->CharacterStateClasses)
	// {
	// 	if (AllStates.Contains(KvpState.Key)) continue;
	// 	AllStates.Emplace(KvpState.Key, NewObject<USmashCharacterState>(this, KvpState.Value));
	// }
	TArray<UActorComponent*> FoundComponents = Character->K2_GetComponentsByClass(UMovementState::StaticClass());
	for (UActorComponent* StateComponent : FoundComponents)
	{
		UMovementState* State = Cast<UMovementState>(StateComponent);
		if (State == nullptr) continue;
		if (State->GetStateId() == EMovementStateId::None) continue;
		
		AllStates.Add(State->GetStateId(), State);
	}
}

void UMovementStateMachine::InitStates()
{
	for (TTuple<EMovementStateId, UMovementState*> Kvp : AllStates)
	{
		Kvp.Value->StateInit(this);
	}
}
