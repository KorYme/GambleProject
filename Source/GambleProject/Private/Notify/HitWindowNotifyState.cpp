// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/HitWindowNotifyState.h"
#include "Notify/HitWindowNotifiable.h"

void UHitWindowNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	TScriptInterface<IHitWindowNotifiable> Notifiable = MeshComp->GetOwner();
	if (Notifiable)
	{
		Notifiable->Execute_OnHitWindowBegin(MeshComp->GetOwner(), WindowName);
	}
}

void UHitWindowNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	TScriptInterface<IHitWindowNotifiable> Notifiable = MeshComp->GetOwner();
	if (Notifiable)
	{
		Notifiable->Execute_OnHitWindowEnd(MeshComp->GetOwner(), WindowName);
	}
}

void UHitWindowNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	TScriptInterface<IHitWindowNotifiable> Notifiable = MeshComp->GetOwner();
	if (Notifiable)
	{
		Notifiable->Execute_OnHitWindowTick(MeshComp->GetOwner(), WindowName, FrameDeltaTime);
	}
}