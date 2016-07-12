// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "BaseCharacter.h"
#include "PlayerClass.h"
#include "Skill.h"

USkill::USkill(FName SkillName, FText Description, uint8 MaxLevel, USkill* ParentSkill) {
	this->SkillName = SkillName;
	this->Description = Description;
	this->MaxLevel = MaxLevel;
	this->ParentSkill = ParentSkill;
}

USkill::~USkill() {

}

bool USkill::CheckRequirements(ABaseCharacter* Character) {
	bool bRightClass = Requirements.Class == NULL
		|| (Requirements.Class != NULL && Requirements.Class == Character->GetPlayerClass());

	bool bRightLevel = Requirements.Level <= 0 
		|| Requirements.Level <= Character->Level;

	bool bEnoughMana = Requirements.Mana <= 0 
		|| Requirements.Mana <= Character->Mana;

	//Need to change that
	bool bHasParent = Requirements.ParentSkill != NULL
		|| Character->GetPlayerClass()->GetSkills().Contains(Requirements.ParentSkill);

	return bRightClass && bRightLevel && bEnoughMana && bHasParent;
}
