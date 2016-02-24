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

	UPROPERTY(VisibleAnywhere, Category = "Action")
	FEventContainer ExecuteEvent;

public:
	UDodge();

	UFUNCTION(BlueprintCallable, Category = "Skill")
	UAnimationAsset* GetAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	void Execute(ABaseCharacter* Executor) override;

	UFUNCTION(Category = "Skill")
	FEventContainer GetEvent();

};
