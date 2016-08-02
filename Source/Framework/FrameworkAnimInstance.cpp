// CC BY-NC 4.0

#include "Framework.h"
#include "UnrealNetwork.h"
#include "Animation/AnimInstance.h"
#include "FrameworkAnimInstance.h"
#include "ActiveSkill.h"
#include "BaseCharacter.h"
#include "Attack.h"
#include "Engine.h"

void UActionActiveNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	UFrameworkAnimInstance* AnimInstance = UFrameworkAnimInstance::TryCast(MeshComp->GetAnimInstance());
	if (AnimInstance != nullptr) {
		AnimInstance->bCanRotate = false;
		AnimInstance->bWeaponCanTick = true;
	}
}

void UActionComboStartNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	UFrameworkAnimInstance* AnimInstance = UFrameworkAnimInstance::TryCast(MeshComp->GetAnimInstance());
	if (AnimInstance != nullptr) {
		AnimInstance->bIsInCombo = true;
		AnimInstance->bWeaponCanTick = false;
		AnimInstance->bCanDecideNextAction = true;

		FTimerDynamicDelegate Delegate;
 		Delegate.BindDynamic(AnimInstance, &UFrameworkAnimInstance::DisableCombo);
		FTimerHandle Handle;
 		AnimInstance->GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, 60.0f, false);
	}
}

void UFrameworkAnimInstance::Attack(UAnimMontage* Montage, uint8 Slot, uint8 MaxCombo, TScriptInterface<IAction> Action) {
	if (Pawn == nullptr) return;
	ABaseCharacter* Character = Cast<ABaseCharacter>(Pawn);
	if (Character == nullptr) return;

	if (bCanDecideNextAction) {
		if (CurrentMontage == Montage) {
			if (CurrentCombo <= MaxCombo) {
				CurrentCombo++;
				SetNextSection(Montage, Slot);
			} else {
				CurrentCombo = 1;
				Montage_Stop(1.0f, CurrentMontage);
				Action->Execute(Character);
			}
		} else {
			if (CurrentMontage != nullptr) {
				Montage_Stop(1.0f, CurrentMontage);
			}
			Action->Execute(Character);
			CurrentMontage = Montage;
			CurrentCombo = 1;
		}
		bCanDecideNextAction = false;
	}
}

void UFrameworkAnimInstance::SetDefaultMontage(ABaseCharacter* Character, TScriptInterface<IAction> Action) {
	Character->SetDefaultAction();
	CurrentMontage = nullptr;
	bCanRotate = true; //TODO move?
}

void UFrameworkAnimInstance::DisableCombo() {
	if (CurrentMontage == nullptr || !bCanDecideNextAction) {
		bIsInCombo = false;
		return;
	}
}

UFrameworkAnimInstance* UFrameworkAnimInstance::TryCast(UAnimInstance* Instance) {
	if (Instance != nullptr) {
		UFrameworkAnimInstance* AnimInstance = Cast<UFrameworkAnimInstance>(Instance);
		if (AnimInstance != nullptr) {
			return AnimInstance;
		} else {
			return nullptr;
		}
	}
	UE_LOG(Debugg, Warning, TEXT("[UFrameworkAnimInstance::Cast] AnimInstance is null"));
	return nullptr;
}

void UFrameworkAnimInstance::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	Pawn = TryGetPawnOwner();
 	ABaseCharacter* Character = Cast<ABaseCharacter>(Pawn);
 	if (Character != nullptr) {
		Character->Attack->GetExecuteEvent()->EndEvent.AddDynamic(this, &UFrameworkAnimInstance::SetDefaultMontage);
 	}
}

void UFrameworkAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Pawn == nullptr) return;
	if (!Pawn->IsValidLowLevel()) return;
	
	bIsInAir = Pawn->GetMovementComponent()->IsFalling();
	Speed = Pawn->GetVelocity().Size();

	//if (Pawn && Pawn->Role < ROLE_Authority) {}
}
