// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BaseCharacter.h"
#include "Action.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExecuteEvent, ABaseCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExecuteEndEvent, ABaseCharacter*, Character);

//That's what I call a fcking bad workaround
//Epic gave me possibility to use Dynamic Delegate as a return value
//but it doesn't work for Dynamic MULTICAST Delegate :(
USTRUCT()
struct FEventContainer {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintAssignable, Category = "Skill")
	FExecuteEvent Event;

	FEventContainer() {}
};

/**
 * 
 */
UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UAction : public UInterface {//, public IEventContainer<FExecuteEvent> {

	GENERATED_UINTERFACE_BODY()

};

class FRAMEWORK_API IAction {

	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual UAnimationAsset* GetAnimation() = 0;

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void Execute(ABaseCharacter* Executor) = 0;
	
	UFUNCTION(Category = "Event")
	virtual FEventContainer GetEvent() = 0;
};
