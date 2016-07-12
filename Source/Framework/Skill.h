// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacter.h"
#include "Skill.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillApplyEvent, USkill*, Skill, ABaseCharacter*, Character);

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

USTRUCT()
struct FSkillRequirements {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float Mana;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	uint8 Level;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	UPlayerClass* Class;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	USkill* ParentSkill;
};

UCLASS(Abstract)
class FRAMEWORK_API USkill : public UObject {

	GENERATED_BODY()

public:
	USkill() : USkill(FName("Skill"), FText::GetEmpty(), 1, NULL) {};
	USkill(FName SkillName, FText Description, uint8 MaxLevel, USkill* ParentSkill);
	~USkill();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Skill")
	FSkillRequirements Requirements;

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

	//UPROPERTY(VisibleAnywhere, Category = "Skill")
	TMap<FString, UObject*> Settings;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual bool CheckRequirements(ABaseCharacter* Character);

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
