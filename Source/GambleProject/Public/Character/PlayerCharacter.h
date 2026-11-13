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
class GAMBLEPROJECT_API UInputBoolValue : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Input Value")
	const bool GetValue() const { return Value; }
	
	UPROPERTY(BlueprintAssignable)
	FInputBoolEvent OnInputEvent;
	
	UFUNCTION(BlueprintCallable)
	void SetValue(bool NewValue)
	{
		TimeSinceLastTriggered = 0.f;
		IsConsumed = false;
		Value = NewValue;
		OnInputEvent.Broadcast(Value);
	}
	
	void Tick(float DeltaTime) { TimeSinceLastTriggered += DeltaTime; }
	
	void Consume() { IsConsumed = true; }
	
private:
	bool Value = false;
	
	float TimeSinceLastTriggered = 1000.f;
	
	bool IsConsumed = true;
};

UCLASS()
class GAMBLEPROJECT_API UInputVectorValue : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Input Value")
	const FVector2D GetValue() const { return Value; }
	
	UPROPERTY(BlueprintAssignable, Category = "Input Value")
	FInputVectorEvent OnInputEvent;
	
	UFUNCTION(BlueprintCallable, Category = "Input Value")
	void Consume()
	{
		IsConsumed = true;
	}
	
	UFUNCTION(BlueprintCallable, Category = "Input Value")
	void SetValue(FVector2D NewValue)
	{
		TimeSinceLastTriggered = 0.f;
		IsConsumed = false;
		Value = NewValue;
		OnInputEvent.Broadcast(Value);
	}
	
	void Tick(float DeltaTime) { TimeSinceLastTriggered += DeltaTime; }
	
private:
	FVector2D Value = FVector2D::ZeroVector;
	
	float TimeSinceLastTriggered = 1000.f;
	
	bool IsConsumed = true;
};

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
