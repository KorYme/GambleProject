// Fill out your copyright notice in the Description page of Project Settings.

#include "Inputs/InputValues.h"

void UInputBoolValue::Tick(float DeltaTime)
{
	TimeSinceLastPressed += DeltaTime;
}

void UInputBoolValue::SetValue(bool NewValue)
{
	if (NewValue)
	{
		TimeSinceLastPressed = 0.f;
		CanBeConsumed = true;
	}
	Value = NewValue;
	OnInputEvent.Broadcast(Value);
}

bool UInputBoolValue::TryConsume()
{
	if (CanBeConsumed)
	{
		CanBeConsumed = false;
		return true;
	}
	return false;
}

void UInputVectorValue::Tick(float DeltaTime)
{
	TimeSinceLastTriggered += DeltaTime;
}

void UInputVectorValue::SetValue(FVector2D NewValue)
{
	if (NewValue != FVector2D::ZeroVector)
	{
		TimeSinceLastTriggered = 0.f;
		CanBeConsumed = false;
	}
	Value = NewValue;
	OnInputEvent.Broadcast(Value);
}

bool UInputVectorValue::TryConsume()
{
	if (CanBeConsumed)
	{
		CanBeConsumed = false;
		return true;
	}
	return false;
}
