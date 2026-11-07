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
	
	virtual void StateEnter(uint8 PreviousStateId) override;
	
	virtual void StateExit(uint8 NextStateId) override;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "StateMachine")
	TObjectPtr<UMovementStateMachine> StateMachine;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "StateMachine")
	void OnStateInit(UMovementStateMachine* InitStateMachine);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "StateMachine")
	void OnStateEnter(EMovementStateId PreviousStateId);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "StateMachine")
	void OnStateExit(EMovementStateId NextStateId);
	
	UFUNCTION(BlueprintGetter, Category = "StateMachine")
	const UMovementStateMachineData* GetMovementData() const { return StateMachine->MovementData; }
};
