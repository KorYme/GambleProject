// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputValues.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputFloatEvent, const float, ValueFloat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputVectorEvent, const FVector2D, ValueVector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputBoolEvent, const bool, ValueBool);

UCLASS()
class GAMBLEPROJECT_API UInputBoolValue : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Input Value")
	bool GetValue() const { return Value; }
	
	UPROPERTY(BlueprintAssignable, Category = "Input Value")
	FInputBoolEvent OnInputEvent;
	
	UFUNCTION(BlueprintCallable, Category = "Input Value")
	void SetValue(bool NewValue);

	void Tick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Input Value")
	void Consume();

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
	FVector2D GetValue() const { return Value; }
	
	UPROPERTY(BlueprintAssignable, Category = "Input Value")
	FInputVectorEvent OnInputEvent;

	UFUNCTION(BlueprintCallable, Category = "Input Value")
	void SetValue(FVector2D NewValue);

	void Tick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Input Value")
	void Consume();
	
private:
	FVector2D Value = FVector2D::ZeroVector;
	
	float TimeSinceLastTriggered = 1000.f;
	
	bool IsConsumed = true;
};