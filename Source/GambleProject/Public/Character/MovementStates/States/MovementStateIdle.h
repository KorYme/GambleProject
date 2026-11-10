// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MovementStates/MovementState.h"
#include "MovementStateIdle.generated.h"

UCLASS()
class GAMBLEPROJECT_API UMovementStateIdle : public UMovementState
{
	GENERATED_BODY()
	
public:	
	virtual void StateTick(float DeltaTime) override;
};
