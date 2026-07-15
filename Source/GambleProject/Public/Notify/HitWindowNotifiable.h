// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HitWindowNotifiable.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UHitWindowNotifiable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMBLEPROJECT_API IHitWindowNotifiable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category="Hit Window Notify")
	void OnHitWindowBegin(const FString& AttackName);
	
	UFUNCTION(BlueprintNativeEvent, Category="Hit Window Notify")
	void OnHitWindowEnd(const FString& AttackName);
	
	UFUNCTION(BlueprintNativeEvent, Category="Hit Window Notify")
	void OnHitWindowTick(const FString& AttackName, const float& AnimDeltaTime);
};