// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerClass.h"
#include "FireBall.h"
#include "Engine.h"
#include "Mage.generated.h"

/**
 * 
 */
UCLASS() //TODO delete and make Mage blueprint
class FRAMEWORK_API UMage : public UPlayerClass {

	GENERATED_BODY()

public:
	UMage() : UPlayerClass() {
		UFireBall* FireBall = NewObject<UFireBall>();
		FireBall->GetExecuteEvent()->ToEvent().AddDynamic(this, &UMage::OnSkillExecute);
		Skills.Add(FireBall);

		bWantsBeginPlay = true;
	};

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSkillExecute(ABaseCharacter* Caster);
};
