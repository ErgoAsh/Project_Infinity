// CC BY-NC 4.0

#pragma once

#include "Animation/AnimInstance.h"
#include "Action.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FrameworkAnimInstance.generated.h"

UCLASS()
class UActionComboStartNotify : public UAnimNotify {

	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};

UCLASS()
class UActionActiveNotify : public UAnimNotify {

	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FRAMEWORK_API UFrameworkAnimInstance : public UAnimInstance {

	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	APawn* Pawn;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation")
	uint8 CurrentCombo = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	float Speed;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	bool bIsInAir = false;

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void SetNextSection(UAnimMontage* Montage, uint8 Slot);

	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* CurrentMontage;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	bool bIsInCombo = false;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	bool bCanRotate = false;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	bool bWeaponCanTick = false;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	bool bCanDecideNextAction = true;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void Attack(UAnimMontage* Montage, uint8 Slot, uint8 MaxCombo, TScriptInterface<IAction> Action);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetDefaultMontage(ABaseCharacter* Character, TScriptInterface<IAction> Action); //?

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void DisableCombo();

	UFUNCTION(BlueprintCallable, Category = "Animation")
	static UFrameworkAnimInstance* TryCast(UAnimInstance* Instance);

	FORCEINLINE bool IsFalling() const { return bIsInAir; }
};
