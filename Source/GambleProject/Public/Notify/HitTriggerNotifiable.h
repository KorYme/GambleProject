// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitTriggerNotifiable.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UHitTriggerNotifiable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMBLEPROJECT_API IHitTriggerNotifiable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category="Hit Trigger Notify")
	void OnHitNotify(const FString& AttackName);
};
