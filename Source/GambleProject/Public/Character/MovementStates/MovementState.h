// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MovementStates/MovementStateId.h"
#include "MovementState.generated.h"

class APlayerCharacter;
class UMovementStateMachine;

UCLASS(Abstract, BluePrintable)
class GAMBLEPROJECT_API UMovementState : public UActorComponent
{
	GENERATED_BODY()
	
public:
	virtual const EMovementStateId GetStateId() const { return EMovementStateId::None; }
	
	UPROPERTY(EditDefaultsOnly)
	EMovementStateId StateId;
	
	// TODO : Implement those events
	UFUNCTION(NotBlueprintable)
	virtual void StateInit(UMovementStateMachine* InitStateMachine);
	
	UFUNCTION(NotBlueprintable)
	virtual void StateEnter(EMovementStateId PreviousStateId);
	
	UFUNCTION(NotBlueprintable)
	virtual void StateExit(EMovementStateId NextStateId);
	
	UFUNCTION(NotBlueprintable)
	virtual void StateTick(float DeltaTime);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "MovementState")
	void OnStateInit(UMovementStateMachine* InitStateMachine);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "MovementState")
	void OnStateEnter(EMovementStateId PreviousStateId);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "MovementState")
	void OnStateExit(EMovementStateId NextStateId);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "MovementState")
	void OnStateTick(float DeltaTime);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerCharacter> Character;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMovementStateMachine> StateMachine;
};
