// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementStateMachine.h"
#include "StateMachine/GenericState.h"
#include "MovementState.generated.h"

class UMovementStateMachineData;
enum class EMovementStateId : uint8;
class UMovementStateMachine;

UCLASS(Abstract)
class GAMBLEPROJECT_API UMovementState : public UGenericState
{
	GENERATED_BODY()
public:
	virtual void StateInit(UGenericStateMachine* InitStateMachine) override;

	virtual void StateEnter(EMovementStateId PreviousStateId);
	
	virtual void StateExit(EMovementStateId NextStateId);
	
	virtual void StateTick(float DeltaTime) override;
	
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
	const UMovementStateMachineData* GetMovementData() const { return StateMachine->MovementData; }
	
	UFUNCTION(BlueprintNativeEvent)
	void MoveCharacter();
	
	virtual void ApplyMovement();
	
	virtual bool CheckForIdle();
	
	bool IsMoving();
	
	virtual bool CheckForWalk();
	
	virtual bool CheckForRun();
	
	virtual bool CheckForGround();
	
	virtual bool CheckForJump();

	virtual bool CheckForFall();
	
	virtual bool CheckForLanding();
};
