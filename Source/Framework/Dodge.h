// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Action.h"
#include "Dodge.generated.h"


class ABaseCharacter;

/**
 * 
 */
UCLASS()
class FRAMEWORK_API UDodge : public UObject, public IAction {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Action")
	UAnimSequence* Animation;

	//UPROPERTY(VisibleAnywhere, Category = "Action")
	UEventContainer* ExecuteEvent;

public:
	UDodge();

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
