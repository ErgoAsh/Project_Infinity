// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Dodge.h"
#include "BaseCharacter.h"
#include "Animation/AnimInstance.h"
#include "Action.h"

UDodge::UDodge() {
	ExecuteEvent = NewObject<UEventContainer>();
}

UAnimationAsset* UDodge::GetAnimation() {
	return Animation.Get();
}

void UDodge::Execute(ABaseCharacter* Executor) {
	if (!Executor->GetMovementComponent()->IsFalling()) {
		Executor->LaunchCharacter((Executor->GetActorForwardVector() + FVector(0, 0, 0.25)) * -3000, true, true);
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
}

// FExecuteEvent& UDodge::OnExecute() {
// 	return Execute;
// }

UEventContainer* UDodge::GetExecuteEvent() {
	return ExecuteEvent;
}