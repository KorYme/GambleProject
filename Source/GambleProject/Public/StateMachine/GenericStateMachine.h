// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerCharacter> Character;
	
protected:
	UPROPERTY()
	TMap<uint8, UGenericState*> AllStates;

	uint8 CurrentStateId;

	UPROPERTY()
	TObjectPtr<UGenericState> CurrentState;
	
	UFUNCTION(BlueprintCallable)
	const UGenericState* GetCurrentState() const { return CurrentState; }
	
	
	virtual TMap<uint8, TSubclassOf<UGenericState>> GetAllState() const;
	
	void ChangeState(uint8 NextStateId);
	
	void InstantiateStates();
	
	void InitStates();
};
