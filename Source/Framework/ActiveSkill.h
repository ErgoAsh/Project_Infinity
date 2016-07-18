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
UCLASS(Abstract, Blueprintable, BlueprintType)
class FRAMEWORK_API UActiveSkill : public USkill, public IAction {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	UEventContainer* ExecuteEvent;

	UPROPERTY(VisibleAnywhere, Category = "Skill") //TODO spawn with TSubclassOf<UEffect> (not IConsequence unfortunately)
	TArray<UEffect*> ConsequenceEffects; //TScript<IConsequence>?

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	TAssetPtr<UAnimationAsset> Animation;

public:
	UActiveSkill();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	uint8 ManaCost;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	uint8 Cooldown;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	TArray<UEffect*> GetConsequences();

	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual void Execute(ABaseCharacter* Executor) override;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual UAnimationAsset* GetAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Event")
	UEventContainer* GetExecuteEvent() override;

};
