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

	UPROPERTY(VisibleAnywhere, Category = "Action")
	FEventContainer ChangeEvent;

public:
	UDefaultAction();

	UFUNCTION(BlueprintCallable, Category = "Action")
	UAnimationAsset* GetAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Execute(ABaseCharacter* Executor) override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	FEventContainer& GetEvent() override;

};
