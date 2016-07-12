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
	return (UAnimationAsset*) Animation;
}

void UAttack::Execute(ABaseCharacter* Executor) {
	//Add UPropertyComponent
	UE_LOG(Debugg, Warning, TEXT("Lel"));
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
}

// FExecuteEvent& UAttack::OnExecute() {
// 	return Execute;
// }

UEventContainer* UAttack::GetExecuteEvent() {
	return ExecuteEvent;
}
