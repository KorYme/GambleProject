// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/GenericStateMachine.h"
#include "StateMachine/GenericState.h"
#include "Character/PlayerCharacter.h"

void UGenericStateMachine::Init(APlayerCharacter* InCharacter)
{
	this->Character = InCharacter;
	GetStates();
	InitStates();
}

void UGenericStateMachine::StateMachineTick(float DeltaTime)
{
	if (CurrentState)
	{
		CurrentState->StateTick(DeltaTime);
	}
}

void UGenericStateMachine::ChangeState(uint8 NextStateId)
{
	if (NextStateId == CurrentStateId) return;
	
	UGenericState** NextState = AllStates.Find(NextStateId);

	// Do nothing if no state is linked to nextStateId
	if (!NextState)
	{
		UE_LOG(LogTemp, Log, TEXT("No state found with id : %i"), NextStateId);
		return;
	}

	if (CurrentState)
	{
		CurrentState->StateExit(NextStateId);
	}

	uint8 PreviousStateID = CurrentStateId;
	CurrentStateId = NextStateId;
	CurrentState = *NextState;

	CurrentState->StateEnter(PreviousStateID);
}

void UGenericStateMachine::GetStates()
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
	// TArray<UActorComponent*> FoundComponents = Character->K2_GetComponentsByClass(UGenericState::StaticClass());
	// for (UActorComponent* StateComponent : FoundComponents)
	// {
	// 	UGenericState* State = Cast<UGenericState>(StateComponent);
	// 	if (State == nullptr) continue;
	// 	if (State->GetStateId() == EMovementStateId::None) continue;
	// 	
	// 	AllStates.Add(State->GetStateId(), State);
	// }
}

void UGenericStateMachine::InitStates()
{
	for (TTuple<uint8, UGenericState*> Kvp : AllStates)
	{
		Kvp.Value->StateInit(this);
	}
}
