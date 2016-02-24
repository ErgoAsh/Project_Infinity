// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skill.h"
#include "Action.h"
#include "Animation/AnimInstance.h"
#include "BaseCharacter.h"
#include "ActiveSkill.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExecuteEvent, ABaseCharacter*, Character);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExecuteEndEvent, ABaseCharacter*, Character);

/**
 * 
 */
UCLASS(Blueprintable, ABSTRACT)
class FRAMEWORK_API UActiveSkill : public USkill, public IAction {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	FEventContainer ExecuteEvent;

	UPROPERTY(BlueprintAssignable, Category = "Skill")
	FExecuteEndEvent ExecuteEndEvent;

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

	UFUNCTION(Category = "Skill")
	FEventContainer GetEvent() override;

};
