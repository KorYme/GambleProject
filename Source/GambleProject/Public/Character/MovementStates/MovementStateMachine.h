// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/GenericStateMachine.h"
#include "MovementStateMachine.generated.h"


class UMovementStateMachineData;
class UMovementState;
enum class EMovementStateId : uint8;
enum class EStateToggleBehaviours : uint8;

UCLASS(BlueprintType, ClassGroup= "State Machine", meta= (BlueprintSpawnableComponent))
class GAMBLEPROJECT_API UMovementStateMachine : public UGenericStateMachine
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(APlayerCharacter* InCharacter, AGambleProjectPlayerController* InController) override;
	
	virtual void Deinitiliaze() override;
	
	UFUNCTION(BlueprintCallable)
	void ChangeState(EMovementStateId NewStateId);
	
	virtual void StateMachineTick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	const EMovementStateId GetCurrentStateId() const { return (EMovementStateId)CurrentStateId; }
	
	UFUNCTION(BlueprintCallable)
	const UMovementState* GetCurrentMovementState() const { return CurrentMovementState; }
	
	UFUNCTION(BlueprintCallable)
	const UMovementStateMachineData* GetMovementData() const { return MovementData; }

protected:
	virtual TMap<uint8, TSubclassOf<UGenericState>> GetAllState() const override;
	
	UPROPERTY()
	TObjectPtr<UMovementState> CurrentMovementState;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMovementStateMachineData> MovementData;
	
	virtual void OnStateChanged(UGenericState* NewCurrentState) override;
	
private:
	UPROPERTY(Config, EditAnywhere, Category = "States")
	TMap<EMovementStateId, TSubclassOf<UMovementState>> CharacterStateClasses;
	
	UPROPERTY(Config, EditAnywhere, Category = "States")
	bool IsStateDebugDisplayed;

#pragma region INPUTS
public:	
	bool IsMoving();
	
	bool IsOnGround();
	
	bool IsFalling();
	
	bool IsJumping();
	
	bool IsJumpingWithBuffer();
	
	bool IsSprinting();
	
	void CheckForSprintBuffer();
	
	void UntoggleSprint();
	
	bool IsCrouching();
	
	void CheckForCrouchBuffer();
	
	void UntoggleCrouch();
	
	bool CanSlide();
	
private:
	UFUNCTION()
	void JumpInput(const bool IsJumping);
	
	UFUNCTION()
	void SprintInput(const bool IsSprinting);
	
	UFUNCTION()
	void CrouchInput(const bool IsCrouching);
	
	bool IsSprintToggled;
	
	bool IsCrouchToggled;
#pragma endregion
};
