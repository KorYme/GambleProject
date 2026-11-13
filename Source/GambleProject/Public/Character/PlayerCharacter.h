// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UInputComponent;
class UEnhancedInputComponent;
class UInputAction;
class UMovementStateMachine;
class UPlayerInputData;
class UInputBoolValue;
class UInputVectorValue;
struct FInputActionValue;

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
	UPROPERTY(EditDefaultsOnly, Category ="Inputs")
	TObjectPtr<UPlayerInputData> InputData;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputVectorValue* MovementInput;

	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputVectorValue* AimInput;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputBoolValue* JumpInput;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputBoolValue* SprintInput;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputBoolValue* CrouchInput;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputBoolValue* FireInput;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputBoolValue* RerollInput;
	
private:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void InputValuesInit();
	
	void InputValuesTick(float DeltaTime);
	
	void OnInputMove(const FInputActionValue& InputActionValue);
	
	void OnInputAim(const FInputActionValue& InputActionValue);
	
	void OnInputJump(const FInputActionValue& InputActionValue);
	
	void OnInputSprint(const FInputActionValue& InputActionValue);
	
	void OnInputCrouch(const FInputActionValue& InputActionValue);
	
	void OnInputFire(const FInputActionValue& InputActionValue);
	
	void OnInputReroll(const FInputActionValue& InputActionValue);
#pragma endregion
};
