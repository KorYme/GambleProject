// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/States/MovementStateIdle.h"
#include "Character/MovementStates/MovementState.h"

void UMovementStateIdle::StateTick(float DeltaTime)
{
	if (CheckForJump()) return;
	if (CheckForFall()) return;
	if (CheckForWalk()) return;
	if (CheckForRun()) return;
	Super::StateTick(DeltaTime);
}
