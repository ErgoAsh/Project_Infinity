// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Action.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExecuteEvent, ABaseCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExecuteEndEvent, ABaseCharacter*, Character);

//That's what I call a bad workaround
//Epic gave me possibility to use Dynamic Delegate as a return value
//but it doesn't work for Dynamic MULTICAST Delegate :(
UCLASS(NotBlueprintable)
class UEventContainer : public UObject {

	GENERATED_BODY()

public:
	UEventContainer() {}

	UPROPERTY(BlueprintAssignable, Category = "Action")
	FOnExecuteEvent Event;
};

/**
 * 
 */
UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UAction : public UInterface {

	GENERATED_UINTERFACE_BODY()

};

class FRAMEWORK_API IAction {

	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual UAnimationAsset* GetAnimation() = 0;

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void Execute(ABaseCharacter* Executor) = 0;
	
	UFUNCTION(BlueprintCallable, Category = "Event")
	virtual UEventContainer* GetExecuteEvent() = 0;

	//DECLARE_EVENT_OneParam(IAction, FExecuteEvent, ABaseCharacter*)
	//virtual FExecuteEvent& OnExecute() = 0;

	//UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	//virtual void OnExecute(ABaseCharacter* Character) = 0;
};
