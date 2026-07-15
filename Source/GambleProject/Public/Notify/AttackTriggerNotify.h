// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttackTriggerNotify.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAMBLEPROJECT_API UAttackTriggerNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override { return TriggerName; }
	
	UPROPERTY(EditAnywhere)
	FString TriggerName;
};
