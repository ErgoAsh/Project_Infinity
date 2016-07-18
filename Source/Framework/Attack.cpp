// CC BY-NC 4.0

#include "Framework.h"
#include "Attack.h"
#include "BaseCharacter.h"
#include "Animation/AnimInstance.h"
#include "Action.h"
#include "Animation/AnimationAsset.h"

UAttack::UAttack() {
	ExecuteEvent = NewObject<UEventContainer>();
}

UAnimationAsset* UAttack::GetAnimation() {
	return Animation.Get();
}

void UAttack::Execute(ABaseCharacter* Executor) {
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

UEventContainer* UAttack::GetExecuteEvent() {
	return ExecuteEvent;
}
