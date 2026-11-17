// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MovementStates/MovementState.h"
#include "MovementStateJump.generated.h"

UCLASS()
class GAMBLEPROJECT_API UMovementStateJump : public UMovementState
{
	GENERATED_BODY()
	
public:
	virtual bool StateEnter(EMovementStateId PreviousStateId) override;
	
	virtual void StateExit(EMovementStateId NextStateId) override;
	
	virtual void StateTick(float DeltaTime) override;
	
	virtual EStateToggleBehaviours GetToggleBehaviour() override;

protected:
	virtual void OnInputJumpTriggered(const bool IsJumping) override;
	
	float JumpTimer;
};
