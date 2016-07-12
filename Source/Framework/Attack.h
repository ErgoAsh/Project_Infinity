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

	//UPROPERTY(VisibleAnywhere, Category = "Action")
	UEventContainer* ExecuteEvent;

public:
	UAttack();

	UFUNCTION(BlueprintCallable, Category = "Action")
	UAnimationAsset* GetAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Execute(ABaseCharacter* Executor) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Action")
	bool bAttackLeft; //May be invalid for weird enemies...

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Action")
	bool bAttackRight;

	//DECLARE_DERIVED_EVENT(UAttack, IAction::FExecuteEvent, FAAAEvent)
	//FExecuteEvent& OnExecute() override;

	//UPROPERTY(BlueprintAssignable, Category = "Event")
	//FExecuteEvent Execute;

	UFUNCTION(BlueprintCallable, Category = "Event")
	UEventContainer* GetExecuteEvent() override;

};
