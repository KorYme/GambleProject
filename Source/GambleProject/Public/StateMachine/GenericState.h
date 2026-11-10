// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericState.generated.h"

class APlayerCharacter;
class UGenericStateMachine;

UCLASS(Abstract, Blueprintable)
class GAMBLEPROJECT_API UGenericState : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void StateInit(UGenericStateMachine* InitStateMachine);
	
	virtual void StateEnter(uint8 PreviousStateId);
	
	virtual void StateExit(uint8 NextStateId);
	
	virtual void StateTick(float DeltaTime);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "StateMachine")
	void OnStateTick(float DeltaTime);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "StateMachine")
	TObjectPtr<APlayerCharacter> Character;
};
