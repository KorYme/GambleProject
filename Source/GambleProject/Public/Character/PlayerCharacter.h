// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UInputComponent;
class UEnhancedInputComponent;
class UInputAction;
struct FInputActionValue;
class UMovementStateMachine;
class UPlayerInputData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputFloatEvent, const float, ValueFloat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputVectorEvent, const FVector2D, ValueVector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputBoolEvent, const bool, ValueBool);

UCLASS()
class GAMBLEPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	const UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	
private:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UMovementStateMachine> MovementStateMachine;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

#pragma region INPUTS
public:
	UPROPERTY(EditDefaultsOnly, Category ="Input")
	TObjectPtr<UPlayerInputData> InputData;
	
	UPROPERTY(BlueprintAssignable, Category = "Input Events")
	FInputVectorEvent OnMoveInputEvent;
	
	UFUNCTION(BlueprintPure, Category ="Input")
	const FVector2D GetMoveInputDirection() const { return CurrentMoveInput; }
	
	UPROPERTY(BlueprintAssignable, Category = "Input Events")
	FInputVectorEvent OnAimInputEvent;
	
	UFUNCTION(BlueprintGetter)
	const FVector2D GetAimInputDirection() const { return CurrentAimInput; }
	
	UPROPERTY(BlueprintAssignable, Category = "Input Events")
	FInputBoolEvent OnJumpInputEvent;
		
	UFUNCTION(BlueprintGetter)
	const bool IsJumpInputPressed() const { return CurrentJumpInput; }
	
	UPROPERTY(BlueprintAssignable, Category = "Input Events")
	FInputBoolEvent OnSprintInputEvent;
			
	UFUNCTION(BlueprintGetter)
	const bool IsSprintInputPressed() const { return CurrentSprintInput; }

	UPROPERTY(BlueprintAssignable, Category = "Input Events")
	FInputBoolEvent OnCrouchInputEvent;
			
	UFUNCTION(BlueprintGetter)
	const bool IsCrouchInputPressed() const { return CurrentCrouchInput; }

	UPROPERTY(BlueprintAssignable, Category = "Input Events")
	FInputBoolEvent OnFireInputEvent;
			
	UFUNCTION(BlueprintGetter)
	const bool IsFireInputPressed() const { return CurrentFireInput; }
	
	UPROPERTY(BlueprintAssignable, Category = "Input Events")
	FInputBoolEvent OnRerollInputEvent;
			
	UFUNCTION(BlueprintGetter)
	const bool IsRerollInputPressed() const { return CurrentRerollInput; }
	
private:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void OnInputMove(const FInputActionValue& InputActionValue);
		
	FVector2D CurrentMoveInput;
	
	void OnInputAim(const FInputActionValue& InputActionValue);
	
	FVector2D CurrentAimInput;
	
	void OnInputJump(const FInputActionValue& InputActionValue);
	
	bool CurrentJumpInput;
	
	void OnInputSprint(const FInputActionValue& InputActionValue);
	
	bool CurrentSprintInput;
	
	void OnInputCrouch(const FInputActionValue& InputActionValue);
	
	bool CurrentCrouchInput;
	
	void OnInputFire(const FInputActionValue& InputActionValue);
	
	bool CurrentFireInput;
	
	void OnInputReroll(const FInputActionValue& InputActionValue);
	
	bool CurrentRerollInput;
#pragma endregion
};
