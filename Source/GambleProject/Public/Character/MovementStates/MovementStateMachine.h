// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/GenericStateMachine.h"
#include "MovementStateMachine.generated.h"


class UMovementStateMachineData;
class UMovementState;
enum class EMovementStateId : uint8;

UCLASS(BlueprintType, ClassGroup= "State Machine", meta= (BlueprintSpawnableComponent))
class GAMBLEPROJECT_API UMovementStateMachine : public UGenericStateMachine
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void ChangeState(EMovementStateId NewStateId);
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMovementStateMachineData> MovementData;
	
	UFUNCTION(BlueprintGetter)
	const EMovementStateId GetCurrentStateId() const { return (EMovementStateId)CurrentStateId; }

protected:
	virtual TMap<uint8, TSubclassOf<UGenericState>> GetAllState() const override;
	
private:
	UPROPERTY(Config, EditAnywhere, Category = "States")
	bool IsStateDebugDisplayed;
	
	UPROPERTY(Config, EditAnywhere, Category = "States")
	TMap<EMovementStateId, TSubclassOf<UMovementState>> CharacterStateClasses;
};
