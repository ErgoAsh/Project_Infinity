// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "ActiveSkill.h"
#include "Animation/SkeletalMeshActor.h"
#include "FrameworkAnimInstance.h"
#include "Engine.h"

UActiveSkill::UActiveSkill() {
	ExecuteEvent = NewObject<UEventContainer>();
}

UAnimMontage* UActiveSkill::GetAnimation() {
	return Animation.Get();
}

TArray<UEffect*> UActiveSkill::GetConsequences() {
	return ConsequenceEffects;
}

void UActiveSkill::Execute(ABaseCharacter* Executor) {
	if (Executor) {
		if (GetAnimation()) {
			UFrameworkAnimInstance* AnimInstance = Cast<UFrameworkAnimInstance>(Executor->GetMesh()->GetAnimInstance());
			if (AnimInstance) {
				AnimInstance->CurrentMontage = GetAnimation();
				AnimInstance->Montage_Play(GetAnimation());
			}
		}
	}
	ExecuteEvent->Event.Broadcast(Executor, this);
}

UEventContainer* UActiveSkill::GetExecuteEvent() {
	return ExecuteEvent;
}


