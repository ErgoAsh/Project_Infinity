// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "PlayerClass.h"
#include "Action.h"
#include "ActiveSkill.h"

UPlayerClass::UPlayerClass() {
	bWantsBeginPlay = true;
}

void UPlayerClass::BeginPlay() {
	for (int32 i = 0; i < Skills.Num(); i++) {
		Skills[i]->Apply();
	}

	Super::BeginPlay();
}

//bool UPlayerClass::RegisterSkill(USkill* Skill) {
//	IAction* SkillAction = Cast<IAction>(Skill);
//	if (SkillAction) {
//		ExecuteEvent.AddUObject((UActiveSkill*) Skill, &UActiveSkill::Execute);
//	}
//	return true;
//}

USkill* UPlayerClass::GetSkill(FName Name) {
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

bool UPlayerClass::ApplyEffect(UEffect* Effect)
{
	return false;
}

bool UPlayerClass::RemoveEffect(UEffect* Effect)
{
	return false;
}

