// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skill.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8 {
	Passive,
	Active,
	Buff 
	//Attack?
};

UENUM(BlueprintType)
enum class EElementType : uint8 {
	Fire,
	Ice,
	Lighting,
	Water,

	Dark,
	Light
};

UCLASS(ABSTRACT)
class FRAMEWORK_API USkill : public UObject {

	GENERATED_BODY()

public:
	USkill() : USkill(FName("Skill"), FText::GetEmpty(), 1, NULL) {};
	USkill(FName SkillName, FText Description, uint8 MaxLevel, USkill* ParentSkill);
	~USkill();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	FName SkillName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	uint8 MaxLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	USkill* ParentSkill;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	ESkillType Type = ESkillType::Passive;

	//UFUNCTION(BlueprintCallable, Category = "Skill")
	//bool CanUse();

	//TODO move to PassiveSkill
	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void Apply();

protected:
	//UFUNCTION(Category = "Skill")
	//virtual bool CheckRequirements() PURE_VIRTUAL(USkill::CanUse, return true;);1

	//CanUse(Player)
	//Use(Player)
	//Cancel
	//CheckRequirements

	//OnSkillUse
	//OnSkillCancel
	//OnSkillCast
	//OnSkillHit
};
