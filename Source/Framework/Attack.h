// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Action.h"
#include "Attack.generated.h"

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

	UFUNCTION(BlueprintCallable, Category = "Skill")
	UAnimationAsset* GetAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	void Execute(ABaseCharacter* Executor) override;

	UFUNCTION(Category = "Skill")
	FEventContainer GetEvent();

};
