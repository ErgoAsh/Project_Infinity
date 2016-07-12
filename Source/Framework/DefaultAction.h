// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Action.h"
#include "DefaultAction.generated.h"

class ABaseCharacter;

/**
 * 
 */
UCLASS()
class FRAMEWORK_API UDefaultAction : public UObject, public IAction {

	GENERATED_BODY() //TODO add somewhere a static instance, maybe in gamemode

	//UPROPERTY(VisibleAnywhere, Category = "Action")
	UEventContainer* ChangeEvent;

public:
	UDefaultAction();

	UFUNCTION(BlueprintCallable, Category = "Action")
	UAnimationAsset* GetAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Execute(ABaseCharacter* Executor) override;

	//DECLARE_DERIVED_EVENT(UAttack, IAction::FExecuteEvent, FExecuteEvent)
	//FExecuteEvent& OnExecute() override;

	//UPROPERTY(BlueprintAssignable, Category = "Event")
	//FExecuteEvent Execute;

	UFUNCTION(BlueprintCallable, Category = "Event")
	UEventContainer* GetExecuteEvent() override;

};
