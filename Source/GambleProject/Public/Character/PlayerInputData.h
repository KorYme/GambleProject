// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerInputData.generated.h"

UCLASS()
class GAMBLEPROJECT_API UPlayerInputData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category ="Move")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category ="Aim")
	TObjectPtr<UInputAction> GamepadAimAction;
	
	UPROPERTY(EditAnywhere, Category ="Aim")
	TObjectPtr<UInputAction> MouseAimAction;
	
	UPROPERTY(EditAnywhere, Category ="Jump")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category ="Sprint")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere, Category ="Crouch")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category ="Fire")
	TObjectPtr<UInputAction> FireAction;
	
	UPROPERTY(EditAnywhere, Category ="Reroll")
	TObjectPtr<UInputAction> RerollAction;
};
