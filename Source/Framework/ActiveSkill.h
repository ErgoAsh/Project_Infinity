// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skill.h"
#include "Action.h"
#include "Animation/AnimInstance.h"
#include "Delegate.h"
#include "BaseCharacter.h"
#include "ScriptDelegates.h"
#include "ActiveSkill.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExecuteEvent, ABaseCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExecuteEndEvent, ABaseCharacter*, Character);

/**
 * 
 */
UCLASS(Blueprintable, ABSTRACT)
class FRAMEWORK_API UActiveSkill : public USkill, public IAction {

	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable, Category = "Skill")
	FExecuteEvent ExecuteEvent;

	UPROPERTY(BlueprintAssignable, Category = "Skill")
	FExecuteEndEvent ExecuteEndEvent;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	uint8 ManaCost;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	uint8 Cooldown;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual void Execute(ABaseCharacter* Executor) override;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	TArray<TMulticastScriptDelegate*> GetEvents() override;

};
