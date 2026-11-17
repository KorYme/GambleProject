// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GenericStateMachine.generated.h"

class AGambleProjectPlayerController;
class UGenericState;
class APlayerCharacter;

UCLASS(Abstract)
class GAMBLEPROJECT_API UGenericStateMachine : public UActorComponent
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(APlayerCharacter* InCharacter, AGambleProjectPlayerController* InController);
	
	virtual void Deinitiliaze();
	
	virtual void StateMachineTick(float DeltaTime);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerCharacter> Character;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGambleProjectPlayerController> Controller;
	
	UFUNCTION(BlueprintCallable)
	float GetCurrentStateTime() { return CurrentStateTime; };
	
	UFUNCTION(BlueprintCallable)
	const UGenericState* GetCurrentState() const { return CurrentState; }
	
protected:
	UPROPERTY()
	TMap<uint8, UGenericState*> AllStates;

	uint8 CurrentStateId;

	UPROPERTY()
	TObjectPtr<UGenericState> CurrentState;
	
	virtual TMap<uint8, TSubclassOf<UGenericState>> GetAllState() const;
	
	void ChangeState(uint8 NextStateId);
	
	virtual void OnStateChanged(UGenericState* NewCurrentState); 
	
	void InstantiateStates();
	
	void InitStates();
	
private:
	float CurrentStateTime;
};
