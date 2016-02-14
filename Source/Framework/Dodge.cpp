// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Dodge.h"
#include "Animation/AnimInstance.h"

UDodge::UDodge() {
	static ConstructorHelpers::FObjectFinder<UAnimSequence> Anim(TEXT(
		"AnimSequence'/Game/Mannequin/Animations/ThirdPersonJump_Start.ThirdPersonJump_Start'"));
	if (Anim.Succeeded()) {
		Animation = Anim.Object;
	}
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

TArray<TMulticastScriptDelegate*> UActiveSkill::GetEvents() {
	TArray<TMulticastScriptDelegate*> Events;
	Events.Add(ExecuteEvent);
	return Events;
}