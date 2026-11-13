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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Walk")
	float WalkSpeed = 300.f;
	
	// Run
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Run")
	float RunSpeed = 600.f;
	
	// Jump
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump")
	float JumpMoveSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump", meta= (ClampMin = 0.f))
	float JumpDuration = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump", meta= (ClampMin = 0.f))
	float JumpMaxHeight = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump", meta= (ClampMin = 0.f, ClampMax = 1.f))
	float JumpAirControl = 1.f;
	
	// Fall
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fall")
	float FallMoveSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fall", meta= (ClampMin = 0.f))
	float FallDuration = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fall", meta= (ClampMin = 0.f, ClampMax = 1.f))
	float FallAirControl = 1.f;
	
	// Crouch
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crouch")
	float CrouchSpeed = 200.f;

	// Slide
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slide")
	float SlideSpeedMultiplier = 1.2f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slide", meta= (ClampMin = 0.f))
	float MinimumSpeedToSlide = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slide", meta= (ClampMin=0.1f))
	float SlideSpeedLossPerSecond = 200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slide", meta= (ClampMin = 0.f, ClampMax = 180.f))
	float SlideMaxRotation = 45.f;
	
	// Game feel feature
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game feel", meta= (ClampMin = 0.f, ClampMax = 1.f))
	float CoyoteJumpTimeFrame = .15f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game feel", meta= (ClampMin = 0.f, ClampMax = 1.f))
	float InputBufferTime = .15f;
	
	// Accessibility feature
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Accessibility")
	bool IsSprintToggle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Accessibility")
	bool IsCrouchToggle;
};
