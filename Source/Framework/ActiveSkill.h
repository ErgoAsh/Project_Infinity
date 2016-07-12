// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skill.h"
#include "Action.h"
#include "Animation/AnimInstance.h"
#include "BaseCharacter.h"
#include "ActiveSkill.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ABSTRACT)
class FRAMEWORK_API UActiveSkill : public USkill, public IAction {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	UEventContainer* ExecuteEvent;

	//UPROPERTY(BlueprintAssignable, Category = "Skill")
	FOnExecuteEndEvent ExecuteEndEvent;

public:
	UActiveSkill();

	//TODO Make them attribute
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	uint8 ManaCost;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	uint8 Cooldown;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual void Execute(ABaseCharacter* Executor) override;

	//Make it pure again
	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual UAnimationAsset* GetAnimation() override;

	//DECLARE_DERIVED_EVENT(UAttack, IAction::FExecuteEvent, FExecuteEvent)
	//FExecuteEvent& OnExecute() override;

	//UPROPERTY(BlueprintAssignable, Category = "Event")
	//FExecuteEvent Execute;

	UFUNCTION(BlueprintCallable, Category = "Event")
	UEventContainer* GetExecuteEvent() override;

};
