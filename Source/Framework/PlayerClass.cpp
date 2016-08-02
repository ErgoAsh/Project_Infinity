// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "PlayerClass.h"
#include "Action.h"
#include "CString.h"
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

int32 UPlayerClass::GetMaxHealth(uint8 Level) {
	FClassData* ClassData = Data->FindRow<FClassData>(FName(*UFrameworkLibrary::ToString(Level)), FString("GENERAL"));
	if (ClassData != nullptr) {
		return ClassData->MaxHealth;
	}
	return -1;
}

int32 UPlayerClass::GetMaxStamina(uint8 Level) {
	FClassData* ClassData = Data->FindRow<FClassData>(FName(*UFrameworkLibrary::ToString(Level)), Context);
	if (ClassData != nullptr) {
		return ClassData->MaxStamina;
	}
	return -1;
}

int32 UPlayerClass::GetMaxMana(uint8 Level) {
	FClassData* ClassData = Data->FindRow<FClassData>(FName(*UFrameworkLibrary::ToString(Level)), Context);
	if (ClassData != nullptr) {
		return ClassData->MaxMana;
	}
	return -1;
}
