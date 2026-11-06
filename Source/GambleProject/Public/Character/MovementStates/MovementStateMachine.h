// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Character/MovementStates/MovementStateId.h"
#include "MovementStateMachine.generated.h"

class UMovementState;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class GAMBLEPROJECT_API UMovementStateMachine : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(APlayerCharacter* InCharacter);
	
	void Tick(float DeltaTime);
	
	APlayerCharacter* GetPlayerCharacter() const { return Character; }
	
	UFUNCTION(BlueprintCallable)
	void ChangeState(EMovementStateId NextStateId);
	
protected:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> Character;

	UPROPERTY()
	TMap<EMovementStateId, UMovementState*> AllStates;

	UPROPERTY(BlueprintReadOnly)
	EMovementStateId CurrentStateId;

	UPROPERTY()
	TObjectPtr<UMovementState> CurrentState;
	
	UFUNCTION(BlueprintCallable)
	const UMovementState* GetCurrentState() const { return CurrentState; }

	void GetStates();
	
	void InitStates();
};
