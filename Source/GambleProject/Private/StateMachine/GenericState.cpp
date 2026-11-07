// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/GenericState.h"

void UGenericState::StateInit(UGenericStateMachine* InitStateMachine)
{
}

void UGenericState::StateEnter(uint8 PreviousStateId)
{
}

void UGenericState::StateExit(uint8 NextStateId)
{
}

void UGenericState::StateTick(float DeltaTime)
{
	OnStateTick(DeltaTime);
}
