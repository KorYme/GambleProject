// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EStateToggleBehaviours : uint8
{
	None = 0,
	CanToggleSprint = 1 << 0,
	UntoggleSprintOnEnter = 1 << 1,
	CanToggleCrouch = 1 << 2,
	UntoggleCrouchOnEnter = 1 << 3,
	All = CanToggleSprint | UntoggleSprintOnEnter | CanToggleCrouch | UntoggleCrouchOnEnter,
};

