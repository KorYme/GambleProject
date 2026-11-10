// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MovementStates/MovementState.h"
#include "MovementStateRun.generated.h"

UCLASS()
class GAMBLEPROJECT_API UMovementStateRun : public UMovementState
{
	GENERATED_BODY()
	
public:
	virtual void StateEnter(EMovementStateId PreviousStateId) override;
	
	virtual void StateTick(float DeltaTime) override;
};
