// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Dodge.h"
#include "BaseCharacter.h"
#include "Animation/AnimInstance.h"
#include "Action.h"

UDodge::UDodge() {
	ExecuteEvent = NewObject<UEventContainer>();
}

UAnimMontage* UDodge::GetAnimation() {
	return Animation.Get();
}

void UDodge::Execute(ABaseCharacter* Executor) {
	if (!Executor->GetMovementComponent()->IsFalling()) {
		Executor->LaunchCharacter((Executor->GetActorForwardVector() + FVector(0, 0, 1)) * -3000, true, true);
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

// FExecuteEvent& UDodge::OnExecute() {
// 	return Execute;
// }

UEventContainer* UDodge::GetExecuteEvent() {
	return ExecuteEvent;
}