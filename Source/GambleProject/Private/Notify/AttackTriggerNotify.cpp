// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AttackTriggerNotify.h"
#include "Notify/HitTriggerNotifiable.h"

void UAttackTriggerNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	TScriptInterface<IHitTriggerNotifiable> Notifiable = MeshComp->GetOwner();
	if (Notifiable)
	{
		Notifiable->Execute_OnHitNotify(MeshComp->GetOwner(), TriggerName);
	}
}
