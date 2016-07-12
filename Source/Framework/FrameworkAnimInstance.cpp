// CC BY-NC 4.0

#include "Framework.h"
#include "UnrealNetwork.h"
#include "Animation/AnimInstance.h"
#include "FrameworkAnimInstance.h"
#include "ActiveSkill.h"

void UFrameworkAnimInstance::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();
	APawn* Pawn = TryGetPawnOwner();
	if (Pawn && Pawn->Role < ROLE_Authority) {
		ABaseCharacter* Char = Cast<ABaseCharacter>(Pawn);
		if (Char) {
			UActiveSkill* Skill = Cast<UActiveSkill>(Char->Action.CurrentAction.GetObjectRef());
			if (Skill) {
				//ExecuteEvent = Skill->GetExecuteEvent().ToEvent();
			}
		}
	}
}
