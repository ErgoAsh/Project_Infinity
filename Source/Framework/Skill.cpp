// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Skill.h"

USkill::USkill(FName SkillName, FText Description, uint8 MaxLevel, USkill* ParentSkill) {
	this->SkillName = SkillName;
	this->Description = Description;
	this->MaxLevel = MaxLevel;
	this->ParentSkill = ParentSkill;
}

USkill::~USkill() {

}
