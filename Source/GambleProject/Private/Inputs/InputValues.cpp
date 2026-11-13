// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs/InputValues.h"

void UInputBoolValue::SetValue(bool NewValue)
{
	TimeSinceLastTriggered = 0.f;
	IsConsumed = false;
	Value = NewValue;
	OnInputEvent.Broadcast(Value);
}

void UInputBoolValue::Tick(float DeltaTime)
{
	TimeSinceLastTriggered += DeltaTime;
}

void UInputBoolValue::Consume()
{
	IsConsumed = true;
}

void UInputVectorValue::SetValue(FVector2D NewValue)
{
	TimeSinceLastTriggered = 0.f;
	IsConsumed = false;
	Value = NewValue;
	OnInputEvent.Broadcast(Value);
}

void UInputVectorValue::Tick(float DeltaTime)
{
	TimeSinceLastTriggered += DeltaTime;
}

void UInputVectorValue::Consume()
{
	IsConsumed = true;
}
