// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MovementStates/MovementState.h"
#include "MovementStateCrouchIdle.generated.h"

UCLASS()
class GAMBLEPROJECT_API UMovementStateCrouchIdle : public UMovementState
{
	GENERATED_BODY()
	
public:
	virtual void StateEnter(EMovementStateId PreviousStateId) override;
	
	virtual void StateExit(EMovementStateId NextStateId) override;
	
	virtual void StateTick(float DeltaTime) override;
};
