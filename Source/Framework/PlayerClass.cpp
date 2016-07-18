// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "PlayerClass.h"
#include "Action.h"
#include "ActiveSkill.h"

UPlayerClass::UPlayerClass() {
	bWantsBeginPlay = true;
}


void UPlayerClass::BeginPlay() {
	for (TSubclassOf<USkill> SkillClass : SkillClasses) {
		USkill* Skill = NewObject<USkill>(this, *SkillClass);
		if (Skill != nullptr) {
			Skills.Add(Skill);
		}
	}
	Super::BeginPlay();
}


USkill* UPlayerClass::GetSkill(FString Name) { //Reference?
	for (USkill* Skill : Skills) {
		if (Name.Compare(Skill->SkillName) == 0) {
			return Skill;
		}
	}
	return NULL;
}

TArray<USkill*> UPlayerClass::GetSkills() {
	return Skills;
}
