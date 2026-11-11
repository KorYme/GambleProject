// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MovementStateMachineData.generated.h"

UCLASS()
class GAMBLEPROJECT_API UMovementStateMachineData : public UDataAsset
{
	GENERATED_BODY()
public:
	// Walk
	UPROPERTY(EditAnywhere, Category = "Walk")
	float WalkSpeed = 300.f;
	
	// Run
	UPROPERTY(EditAnywhere, Category = "Run")
	float RunSpeed = 600.f;
	
	// Jump
	UPROPERTY(EditAnywhere, Category = "Jump")
	float JumpMoveSpeed = 400.f;

	UPROPERTY(EditAnywhere, Category = "Jump")
	float JumpDuration = 1.f;

	UPROPERTY(EditAnywhere, Category = "Jump")
	float JumpMaxHeight = 100.f;

	UPROPERTY(EditAnywhere, Category = "Jump")
	float JumpAirControl = 1.f;
	
	// Fall
	UPROPERTY(EditAnywhere, Category = "Fall")
	float FallMoveSpeed = 400.f;

	UPROPERTY(EditAnywhere, Category = "Fall")
	float FallDuration = 1.f;

	UPROPERTY(EditAnywhere, Category = "Fall")
	float FallAirControl = 1.f;
	
	// Crouch
	UPROPERTY(EditAnywhere, Category = "Crouch")
	float CrouchSpeed = 200.f;

	// SlideSpeed
	UPROPERTY(EditAnywhere, Category = "Slide")
	float SlideSpeed = 400.f;
};
