// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/GenericStateMachine.h"
#include "StateMachine/GenericState.h"
#include "Character/PlayerCharacter.h"

void UGenericStateMachine::Init(APlayerCharacter* InCharacter, AGambleProjectPlayerController* InController)
{
	this->Character = InCharacter;
	this->Controller = InController;
	InstantiateStates();
	InitStates();
}

void UGenericStateMachine::StateMachineTick(float DeltaTime)
{
	if (CurrentState)
	{
		CurrentState->StateTick(DeltaTime);
	}
}

TMap<uint8, TSubclassOf<UGenericState>> UGenericStateMachine::GetAllState() const
{
	return TMap<uint8, TSubclassOf<UGenericState>>();
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

void UGenericStateMachine::InstantiateStates()
{
	for (TTuple<uint8, TSubclassOf<UGenericState>> KvpState : GetAllState())
	{
		if (AllStates.Contains(KvpState.Key)) continue;
		AllStates.Emplace(KvpState.Key, NewObject<UGenericState>(this, KvpState.Value));
	}
}

void UGenericStateMachine::InitStates()
{
	for (TTuple<uint8, UGenericState*> Kvp : AllStates)
	{
		Kvp.Value->StateInit(this);
	}
	int a = 0;
}
