// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EMovementStateId : uint8
{
	None = 0,
	Idle,
	Walk,
	Run,
	Jump,
	Fall,
	Slide,
	WallRun
};