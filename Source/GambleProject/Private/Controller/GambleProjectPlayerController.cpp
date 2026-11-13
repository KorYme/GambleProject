// Copyright Epic Games, Inc. All Rights Reserved.


#include "Controller/GambleProjectPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "GambleProject.h"
#include "Inputs/InputValues.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "Inputs/PlayerInputData.h"
#include "Variant_GambleProto/GambleProjectCameraManager.h"

AGambleProjectPlayerController::AGambleProjectPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AGambleProjectCameraManager::StaticClass();
}

void AGambleProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	InputValuesInit();

	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);
		} 
		else 
		{
			UE_LOG(LogGambleProject, Error, TEXT("Could not spawn mobile controls widget."));
		}
	}
}

void AGambleProjectPlayerController::Tick(float DeltaTime)
{
	InputValuesTick(DeltaTime);
	Super::Tick(DeltaTime);
}

void AGambleProjectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Cozntext
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
		SetupPlayerInputComponent(InputComponent);
	}
}

void AGambleProjectPlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputData->MoveAction, ETriggerEvent::Triggered, this, &AGambleProjectPlayerController::OnInputMove);
		EnhancedInputComponent->BindAction(InputData->MoveAction, ETriggerEvent::Completed, this, &AGambleProjectPlayerController::OnInputMove);
 
		EnhancedInputComponent->BindAction(InputData->MouseAimAction, ETriggerEvent::Triggered, this, &AGambleProjectPlayerController::OnInputAim);
		EnhancedInputComponent->BindAction(InputData->GamepadAimAction, ETriggerEvent::Triggered, this, &AGambleProjectPlayerController::OnInputAim);
		
		EnhancedInputComponent->BindAction(InputData->JumpAction, ETriggerEvent::Started, this, &AGambleProjectPlayerController::OnInputJump);
		EnhancedInputComponent->BindAction(InputData->JumpAction, ETriggerEvent::Completed, this, &AGambleProjectPlayerController::OnInputJump);
		
		EnhancedInputComponent->BindAction(InputData->SprintAction, ETriggerEvent::Started, this, &AGambleProjectPlayerController::OnInputSprint);
		EnhancedInputComponent->BindAction(InputData->SprintAction, ETriggerEvent::Completed, this, &AGambleProjectPlayerController::OnInputSprint);
		
		EnhancedInputComponent->BindAction(InputData->CrouchAction, ETriggerEvent::Started, this, &AGambleProjectPlayerController::OnInputCrouch);
		EnhancedInputComponent->BindAction(InputData->CrouchAction, ETriggerEvent::Completed, this, &AGambleProjectPlayerController::OnInputCrouch);

		EnhancedInputComponent->BindAction(InputData->FireAction, ETriggerEvent::Started, this, &AGambleProjectPlayerController::OnInputFire);
		EnhancedInputComponent->BindAction(InputData->FireAction, ETriggerEvent::Completed, this, &AGambleProjectPlayerController::OnInputFire);
		
		EnhancedInputComponent->BindAction(InputData->RerollAction, ETriggerEvent::Started, this, &AGambleProjectPlayerController::OnInputReroll);
		EnhancedInputComponent->BindAction(InputData->RerollAction, ETriggerEvent::Completed, this, &AGambleProjectPlayerController::OnInputReroll);
	}
	else
	{
		UE_LOG(LogGambleProject, Error, TEXT("'%s' Failed to find an Enhanced Input Component!"), *GetNameSafe(this));
	}
}

void AGambleProjectPlayerController::InputValuesInit()
{
	MovementInput = NewObject<UInputVectorValue>();
	AimInput = NewObject<UInputVectorValue>();
	JumpInput = NewObject<UInputBoolValue>();
	SprintInput = NewObject<UInputBoolValue>();
	CrouchInput = NewObject<UInputBoolValue>();
	FireInput = NewObject<UInputBoolValue>();
	RerollInput = NewObject<UInputBoolValue>();
}

void AGambleProjectPlayerController::InputValuesTick(float DeltaTime)
{
	MovementInput->Tick(DeltaTime);
	AimInput->Tick(DeltaTime);
	JumpInput->Tick(DeltaTime);
	SprintInput->Tick(DeltaTime);
	CrouchInput->Tick(DeltaTime);
	FireInput->Tick(DeltaTime);
	RerollInput->Tick(DeltaTime);
}

void AGambleProjectPlayerController::OnInputMove(const FInputActionValue& InputActionValue)
{
	MovementInput->SetValue(InputActionValue.Get<FVector2D>());
}

void AGambleProjectPlayerController::OnInputAim(const FInputActionValue& InputActionValue)
{
	// AddControllerYawInput(AimInput->GetValue().X);
	// AddControllerPitchInput(AimInput->GetValue().Y);
	AimInput->SetValue(InputActionValue.Get<FVector2D>());
}

void AGambleProjectPlayerController::OnInputJump(const FInputActionValue& InputActionValue)
{
	JumpInput->SetValue(InputActionValue.Get<bool>());
}

void AGambleProjectPlayerController::OnInputSprint(const FInputActionValue& InputActionValue)
{
	SprintInput->SetValue(InputActionValue.Get<bool>());
}

void AGambleProjectPlayerController::OnInputCrouch(const FInputActionValue& InputActionValue)
{
	CrouchInput->SetValue(InputActionValue.Get<bool>());
}

void AGambleProjectPlayerController::OnInputFire(const FInputActionValue& InputActionValue)
{
	FireInput->SetValue(InputActionValue.Get<bool>());
}

void AGambleProjectPlayerController::OnInputReroll(const FInputActionValue& InputActionValue)
{
	RerollInput->SetValue(InputActionValue.Get<bool>());
}
