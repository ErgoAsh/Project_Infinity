// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "ActiveSkill.h"
#include "Animation/SkeletalMeshActor.h"
#include "Engine.h"

UActiveSkill::UActiveSkill() {
	ExecuteEvent = NewObject<UEventContainer>();
}

UAnimationAsset* UActiveSkill::GetAnimation() {
	return Animation.Get();
}

TArray<UEffect*> UActiveSkill::GetConsequences() {
	return ConsequenceEffects;
}

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
	ExecuteEvent->Event.Broadcast(Executor, this);
	//TODO wait for sth and broadcast ExecuteEndEvent
}

// FExecuteEvent& UActiveSkill::OnExecute() {
// 	return Execute;
// }

UEventContainer* UActiveSkill::GetExecuteEvent() {
	return ExecuteEvent;
}


