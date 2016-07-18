// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Action.h"
#include "DefaultAction.generated.h"

class ABaseCharacter;

/**
 * 
 */
UCLASS(NotBlueprintable)
class FRAMEWORK_API UDefaultAction : public UObject, public IAction {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Action")
	UEventContainer* ChangeEvent;

public:
	UDefaultAction();

	UFUNCTION(BlueprintCallable, Category = "Action")
	UAnimationAsset* GetAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Execute(ABaseCharacter* Executor) override;

	UFUNCTION(BlueprintCallable, Category = "Event")
	UEventContainer* GetExecuteEvent() override;

};
