// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Action.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExecuteEvent, ABaseCharacter*, Character, TScriptInterface<IAction>, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExecuteEndEvent, ABaseCharacter*, Character, TScriptInterface<IAction>, Action);

//That's what I call a bad workaround
//Epic gave me possibility to use Dynamic Delegate as a return value
//but it doesn't work for Dynamic MULTICAST Delegate :(
UCLASS(NotBlueprintable)
class UEventContainer : public UObject {

	GENERATED_BODY()

public:
	UEventContainer() {}

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnExecuteEvent Event;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnExecuteEndEvent EndEvent;
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
	virtual UAnimationAsset* GetAnimation() = 0; //Montage instead?

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void Execute(ABaseCharacter* Executor) = 0;
	
	UFUNCTION(BlueprintCallable, Category = "Event")
	virtual UEventContainer* GetExecuteEvent() = 0;
};
