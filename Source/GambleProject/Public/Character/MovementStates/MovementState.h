// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementStateMachine.h"
#include "StateToggleBehaviours.h"
#include "StateMachine/GenericState.h"
#include "MovementState.generated.h"

enum class EMovementStateId : uint8;
class UMovementStateMachineData;
class UMovementStateMachine;

UCLASS(Abstract)
class GAMBLEPROJECT_API UMovementState : public UGenericState
{
	GENERATED_BODY()
public:
	virtual void StateInit(UGenericStateMachine* InitStateMachine) override;
	
	virtual bool StateEnter(EMovementStateId PreviousStateId);
	
	virtual void StateExit(EMovementStateId NextStateId);
	
	virtual void StateTick(float DeltaTime) override;
	
	virtual void OnInputJumpTriggered(const bool IsJumping);
	
	virtual EStateToggleBehaviours GetToggleBehaviour() { return EStateToggleBehaviours::None; };
	
private:
	virtual void StateEnter(uint8 PreviousStateId) final override;
	
	virtual void StateExit(uint8 NextStateId) final override;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "StateMachine")
	TObjectPtr<UMovementStateMachine> StateMachine;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "StateMachine")
	void OnStateInit(UMovementStateMachine* InitStateMachine);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "StateMachine")
	void OnStateEnter(EMovementStateId PreviousStateId);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "StateMachine")
	void OnStateExit(EMovementStateId NextStateId);
	
	UFUNCTION(BlueprintPure, Category = "StateMachine")
	const UMovementStateMachineData* GetMovementData() const { return StateMachine->GetMovementData(); }
	
	bool ChangeForStateIf(EMovementStateId NewStateId, bool ShouldChangeState);
	
	UFUNCTION(BlueprintNativeEvent)
	void MoveCharacter();
	
	virtual void ApplyMovement();
	
	bool IsMoving();
	
	bool IsOnGround();
	
	bool IsFalling();
	
	bool IsJumping();
	
	bool IsJumpingWithBuffer();
	
	bool IsSprinting();
	
	bool IsSprintingWithBuffer();	
	
	void UntoggleSprint();
	
	bool IsCrouching();
	
	bool IsCrouchingWithBuffer();
	
	void UntoggleCrouch();
	
	bool CanSlide();
	
};
