// CC BY-NC 4.0

#include "Framework.h"
#include "Attack.h"

UDodge::UDodge() {
	Animation = 
}

UAnimationAsset* UDodge::GetAnimation() {
	return (UAnimationAsset*) Animation;
}

void UDodge::Execute(ABaseCharacter* Executor) {
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

TArray<IDelegateInstance*> UDodge::GetEvents() {
	TArray<IDelegateInstance*> Events;
	Events.Add(ExecuteEvent);
	return Events;
}