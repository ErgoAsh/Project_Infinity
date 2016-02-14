// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Action.h"
#include "Engine.h"
#include "Animation/AnimInstance.h"

UAction::UAction(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer) {

}

UAnimationAsset* IAction::GetAnimation() {
	unimplemented();
	return NULL;
}

void IAction::Execute(ABaseCharacter* Executor) {
	unimplemented();
}

//void IAction::Execute_Implementation(UAnimInstance* AnimInstance) {
//	if (AnimInstance) {
//		UAnimMontage* Montage = Cast<UAnimMontage>(GetAnimation());
//		if (Montage) {
//			AnimInstance->Montage_Play(Montage);
//		} else {
//			UAnimSequenceBase* Sequence = Cast<UAnimSequenceBase>(GetAnimation());
//			if (Sequence) {
//				AnimInstance->PlaySlotAnimationAsDynamicMontage(Sequence, NAME_None);
//			} else {
//				print("[Action.h] Invalid animation asset found");
//			}
//		}
//	}
//}

//bool IAction::Execute_Validate(UAnimInstance* AnimInstance) {
//	if (AnimInstance) {
//		if (GetAnimation()) {
//			return true;
//		}
//	}
//	return false;
//}
