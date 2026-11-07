// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GenericStateMachine.generated.h"

class UGenericState;
class APlayerCharacter;

UCLASS(Abstract)
class GAMBLEPROJECT_API UGenericStateMachine : public UActorComponent
{
	GENERATED_BODY()
	
public:
	void Init(APlayerCharacter* InCharacter);
	
	void StateMachineTick(float DeltaTime);
	
	APlayerCharacter* GetPlayerCharacter() const { return Character; }
	
	
protected:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> Character;

	UPROPERTY()
	TMap<uint8, UGenericState*> AllStates;

	UPROPERTY(BlueprintReadOnly)
	uint8 CurrentStateId;

	UPROPERTY()
	TObjectPtr<UGenericState> CurrentState;
	
	UFUNCTION(BlueprintCallable)
	const UGenericState* GetCurrentState() const { return CurrentState; }
	
	void ChangeState(uint8 NextStateId);
	
	virtual void GetStates();
	
	void InitStates();
};
