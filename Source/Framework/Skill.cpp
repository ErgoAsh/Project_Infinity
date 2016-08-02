// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "BaseCharacter.h"
#include "PlayerClass.h"
#include "Skill.h"

USkill::USkill() {

}

void USkill::BeginPlay() {

}


bool USkill::CheckRequirements(ABaseCharacter* Character) {
	bool bRightClass = Requirements.Class == NULL
		|| (Requirements.Class != NULL && Requirements.Class == Character->GetPlayerClass());

	bool bRightLevel = Requirements.Level <= 0 
		|| Requirements.Level <= Character->GetLevel();

	bool bEnoughMana = Requirements.Mana <= 0
		|| Requirements.Mana <= Character->GetMana();

	bool bHasParent = true;
	if (*Requirements.ParentSkill != NULL) {
		bHasParent = false;
		for (USkill* Skill : Character->GetPlayerClass()->GetSkills()) {
			if (Skill->GetClass()->IsChildOf(*Requirements.ParentSkill)) {
				bHasParent = true;
				break;
			}
		}
	}

	return bRightClass && bRightLevel && bEnoughMana && bHasParent;
}