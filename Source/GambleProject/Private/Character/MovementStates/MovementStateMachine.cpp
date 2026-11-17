// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementStates/MovementStateMachine.h"

#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementState.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "Character/MovementStates/StateToggleBehaviours.h"
#include "Controller/GambleProjectPlayerController.h"
#include "Engine/Engine.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Inputs/InputValues.h"


void UMovementStateMachine::Initialize(APlayerCharacter* InCharacter, AGambleProjectPlayerController* InController)
{
	Super::Initialize(InCharacter, InController);
	Controller->JumpInput->OnInputEvent.AddDynamic(this, &UMovementStateMachine::JumpInput);
	Controller->SprintInput->OnInputEvent.AddDynamic(this, &UMovementStateMachine::SprintInput);
	Controller->CrouchInput->OnInputEvent.AddDynamic(this, &UMovementStateMachine::CrouchInput);
}

void UMovementStateMachine::Deinitiliaze()
{
	Controller->JumpInput->OnInputEvent.RemoveDynamic(this, &UMovementStateMachine::JumpInput);
	Controller->SprintInput->OnInputEvent.RemoveDynamic(this, &UMovementStateMachine::SprintInput);
	Controller->CrouchInput->OnInputEvent.RemoveDynamic(this, &UMovementStateMachine::CrouchInput);
	Super::Deinitiliaze();
}

void UMovementStateMachine::ChangeState(EMovementStateId NewStateId)
{
	Super::ChangeState((uint8)NewStateId);
}

void UMovementStateMachine::StateMachineTick(float DeltaTime)
{
	if (IsStateDebugDisplayed && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, UEnum::GetValueAsString(GetCurrentStateId()));
	}
	Super::StateMachineTick(DeltaTime);
}

TMap<uint8, TSubclassOf<UGenericState>> UMovementStateMachine::GetAllState() const
{
	TMap<uint8, TSubclassOf<UGenericState>> Map;
	for (const TPair<EMovementStateId, TSubclassOf<UMovementState>>& it : CharacterStateClasses)
	{
		Map.Emplace((uint8)it.Key, it.Value);
	}
	return Map;
}

void UMovementStateMachine::OnStateChanged(UGenericState* NewCurrentState)
{
	CurrentMovementState = Cast<UMovementState>(NewCurrentState);
	Super::OnStateChanged(NewCurrentState);
}

bool UMovementStateMachine::IsMoving()
{
	return Controller->MovementInput->GetValue().SquaredLength() > 0;
}

bool UMovementStateMachine::IsOnGround()
{
	return Character->GetMovementComponent()->IsMovingOnGround();
}

bool UMovementStateMachine::IsFalling()
{
	return Character->GetMovementComponent()->IsFalling();
}

bool UMovementStateMachine::IsJumping()
{
	return Controller->JumpInput->GetValue();
}

bool UMovementStateMachine::IsJumpingWithBuffer()
{
	return Controller->JumpInput->HasBeenTriggeredSince(MovementData->InputBufferTime) && Controller->JumpInput->TryConsume();
}

bool UMovementStateMachine::IsSprinting()
{
	return MovementData->EnableSprintToggle ? IsSprintToggled : Controller->SprintInput->GetValue();
}

void UMovementStateMachine::CheckForSprintBuffer()
{
	if (Controller->SprintInput->HasBeenTriggeredSince(MovementData->InputBufferTime) && Controller->SprintInput->TryConsume())
	{
		IsSprintToggled = !IsSprintToggled;
	}
}

void UMovementStateMachine::UntoggleSprint()
{
	IsSprintToggled = false;
}

bool UMovementStateMachine::IsCrouching()
{
	return MovementData->EnableCrouchToggle ? IsCrouchToggled : Controller->CrouchInput->GetValue();
}

void UMovementStateMachine::CheckForCrouchBuffer()
{
	if (Controller->CrouchInput->HasBeenTriggeredSince(MovementData->InputBufferTime) && Controller->CrouchInput->TryConsume())
	{
		IsCrouchToggled = !IsCrouchToggled;
	}
}

void UMovementStateMachine::UntoggleCrouch()
{
	IsCrouchToggled = false;
}

bool UMovementStateMachine::CanSlide()
{
	float velocity = Character->GetVelocity().Length();
	float forwardInput = Controller->MovementInput->GetValue().Y;
	return IsCrouching() && velocity > MovementData->MinimumSpeedToSlide && forwardInput > 0;
}

void UMovementStateMachine::JumpInput(const bool IsJumping)
{
	CurrentMovementState->OnInputJumpTriggered(IsJumping);
}

void UMovementStateMachine::SprintInput(const bool IsSprinting)
{
	if (MovementData->EnableSprintToggle && IsSprinting && 
		((uint8)CurrentMovementState->GetToggleBehaviour() & (uint8)EStateToggleBehaviours::CanToggleSprint) != 0)
	{
		IsSprintToggled = !IsSprintToggled;
		Controller->SprintInput->TryConsume();
	}
}

void UMovementStateMachine::CrouchInput(const bool IsCrouching)
{
	if (MovementData->EnableCrouchToggle && IsCrouching && 
		((uint8)CurrentMovementState->GetToggleBehaviour() & (uint8)EStateToggleBehaviours::CanToggleCrouch) != 0)
	{
		IsCrouchToggled = !IsCrouchToggled;
		Controller->CrouchInput->TryConsume();
	}
}
