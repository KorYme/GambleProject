// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UInputComponent;
class UEnhancedInputComponent;
class UInputAction;
class UMovementStateMachine;
class UPlayerInputData;
class UInputBoolValue;
class UInputVectorValue;
class AGambleProjectPlayerController;
struct FInputActionValue;

UCLASS()
class GAMBLEPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	const UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	
private:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UMovementStateMachine> MovementStateMachine;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
	
	UPROPERTY(BlueprintReadOnly, Category="Gamble Project Controller", meta = (AllowPrivateAccess = "true"))
	AGambleProjectPlayerController* PlayerController;
};
