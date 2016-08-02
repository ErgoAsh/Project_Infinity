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

UAnimMontage* UAttack::GetAnimation() {
	return Montage;
}

void UAttack::Execute(ABaseCharacter* Executor) {
	if (GetAnimation()) {
		UFrameworkAnimInstance* AnimInstance = Cast<UFrameworkAnimInstance>(Executor->GetMesh()->GetAnimInstance());
		if (AnimInstance) {
			if (!AnimInstance->IsFalling()) {
				AnimInstance->Montage_Play(GetAnimation());
				ExecuteEvent->Event.Broadcast(Executor, this);
			}
		}
	}
}

UEventContainer* UAttack::GetExecuteEvent() {
	return ExecuteEvent;
}
