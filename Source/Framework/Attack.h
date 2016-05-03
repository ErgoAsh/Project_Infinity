// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Action.h"
#include "Attack.generated.h"

class ABaseCharacter;

/**
 * 
 */
UCLASS()
class FRAMEWORK_API UAttack : public UObject, public IAction {

	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Action")
	UAnimSequence* Animation;

	UPROPERTY(VisibleAnywhere, Category = "Action")
	FEventContainer ExecuteEvent;

public:
	UAttack();

	UFUNCTION(BlueprintCallable, Category = "Action")
	UAnimationAsset* GetAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Execute(ABaseCharacter* Executor) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Action")
	bool bAttackLeft;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Action")
	bool bAttackRight;

	UFUNCTION(Category = "Action")
	FEventContainer& GetEvent();

};
