// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MovementStates/MovementState.h"
#include "MovementStateFall.generated.h"

/**
 * 
 */
UCLASS()
class GAMBLEPROJECT_API UMovementStateFall : public UMovementState
{
	GENERATED_BODY()
	
public:
	virtual void StateEnter(EMovementStateId PreviousStateId) override;
	
	virtual void StateExit(EMovementStateId NextStateId) override;
	
	virtual void StateTick(float DeltaTime) override;
	
private:
	bool CanCoyoteJump;
};
