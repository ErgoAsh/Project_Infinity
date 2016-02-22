// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "ActiveSkill.h"
#include "Animation/SkeletalMeshActor.h"
#include "Engine.h"
#include "ScriptDelegates.h"

void UActiveSkill::Execute(ABaseCharacter* Executor) {
	if (Executor) {
		if (GetAnimation()) {
			UAnimSequenceBase* Sequence = Cast<UAnimSequenceBase>(GetAnimation());
			if (Sequence) {
				//TODO add somehow overriding animations, not additive
				Executor->GetMesh()->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(
					Sequence, TEXT("DefaultSlot"));
			}
		}
	}
	ExecuteEvent.Broadcast(Executor);
	//TODO wait for sth and broadcast ExecuteEndEvent
}

TArray<TDelegateInstanceInterface*> UActiveSkill::GetEvents() {
	TArray<TDelegateInstanceInterface*> Events;
	Events.Add(ExecuteEvent);
	Events.Add(ExecuteEndEvent);
	return Events;
}


