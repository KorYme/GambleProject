// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MovementStates/States/MovementStateSlide.h"
#include "Character/PlayerCharacter.h"
#include "Character/MovementStates/MovementStateId.h"
#include "Character/MovementStates/MovementStateMachineData.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UMovementStateSlide::StateEnter(EMovementStateId PreviousStateId)
{
	if (ChangeForStateIf(EMovementStateId::Jump, IsJumpingWithBuffer())) return false;
	
	if (Character)
	{
		Character->GetCharacterMovement()->MaxWalkSpeedCrouched = Character->GetVelocity().Length() * GetMovementData()->SlideSpeedMultiplier;
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		Character->Crouch();
	}
	return Super::StateEnter(PreviousStateId);
}

void UMovementStateSlide::StateExit(EMovementStateId NextStateId)
{
	if (Character)
	{
		switch (NextStateId)
		{
			case EMovementStateId::CrouchIdle:
			case EMovementStateId::CrouchWalk:
			case EMovementStateId::Slide:
				break;
			default:
				Character->UnCrouch();
				break;
		}
	}
	return Super::StateExit(NextStateId);
}

void UMovementStateSlide::StateTick(float DeltaTime)
{
	Character->GetCharacterMovement()->MaxWalkSpeedCrouched -= GetMovementData()->SlideSpeedLossPerSecond * DeltaTime;
	if (ChangeForStateIf(EMovementStateId::Run, !IsCrouching())) return;
	if (ChangeForStateIf(EMovementStateId::CrouchIdle, !IsMoving())) return;
	if (Character->GetCharacterMovement()->MaxWalkSpeedCrouched <= GetMovementData()->CrouchSpeed)
	{
		StateMachine->ChangeState(EMovementStateId::CrouchWalk);
		return;
	}
	
	MoveCharacter();
	Super::StateTick(DeltaTime);
}

EStateToggleBehaviours UMovementStateSlide::GetToggleBehaviour()
{
	return (EStateToggleBehaviours)((uint8)EStateToggleBehaviours::CanToggleCrouch 
		| (uint8)EStateToggleBehaviours::CanToggleSprint);
}
