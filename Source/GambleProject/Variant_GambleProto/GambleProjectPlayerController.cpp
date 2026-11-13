// Copyright Epic Games, Inc. All Rights Reserved.


#include "GambleProjectPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "GambleProjectCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "GambleProject.h"
#include "Widgets/Input/SVirtualJoystick.h"

AGambleProjectPlayerController::AGambleProjectPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AGambleProjectCameraManager::StaticClass();
}

void AGambleProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();

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
		// // Bind action to controller once
		// if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
		// {
		// 	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMove);
		// 	EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnLook);
		// 	EnhancedInput->BindAction(PrimaryAction, ETriggerEvent::Started, this, &AMyPlayerController::OnPrimaryAction);
		// }
	}
}