// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Action.h"
#include "Attack.generated.h"

class ABaseCharacter;

/**
 * 
 */
UCLASS(Blueprintable)
class FRAMEWORK_API UAttack : public UObject, public IAction {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Action")
	UEventContainer* ExecuteEvent;

public:
	UAttack();

	UPROPERTY(VisibleAnywhere, Category = "Action")
	class AWeapon* HoldedWeapon;

	UPROPERTY(VisibleAnywhere, Category = "Action")
	UAnimMontage* Montage;

	UFUNCTION(BlueprintCallable, Category = "Action")
	UAnimMontage* GetAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Execute(ABaseCharacter* Executor) override;

	UFUNCTION(BlueprintCallable, Category = "Event")
	UEventContainer* GetExecuteEvent() override;

};
