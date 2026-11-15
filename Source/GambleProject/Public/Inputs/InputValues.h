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
	void Tick(float DeltaTime);

	UPROPERTY(BlueprintAssignable, Category = "Input Value")
	FInputBoolEvent OnInputEvent;
	
	UFUNCTION(BlueprintPure, Category = "Input Value")
	bool GetValue() const { return Value; }
	
	UFUNCTION(BlueprintCallable, Category = "Input Value")
	void SetValue(bool NewValue);

	UFUNCTION(BlueprintCallable, Category = "Input Value")
	bool HasBeenTriggeredSince(float TimeBuffer = 0.f) const { return TimeSinceLastPressed <= TimeBuffer; }
	
	UFUNCTION(BlueprintCallable, Category = "Input Value")
	bool TryConsume();

private:
	bool Value = false;
	
	float TimeSinceLastPressed = 1000.f;
	
	bool CanBeConsumed = false;
};

UCLASS()
class GAMBLEPROJECT_API UInputVectorValue : public UObject
{
	GENERATED_BODY()
	
public:
	void Tick(float DeltaTime);
	
	UPROPERTY(BlueprintAssignable, Category = "Input Value")
	FInputVectorEvent OnInputEvent;

	UFUNCTION(BlueprintPure, Category = "Input Value")
	FVector2D GetValue() const { return Value; }

	UFUNCTION(BlueprintCallable, Category = "Input Value")
	void SetValue(FVector2D NewValue);

	UFUNCTION(BlueprintCallable, Category = "Input Value")
	bool TryConsume();
	
private:
	FVector2D Value = FVector2D::ZeroVector;
	
	float TimeSinceLastTriggered = 1000.f;
	
	bool CanBeConsumed = true;
};