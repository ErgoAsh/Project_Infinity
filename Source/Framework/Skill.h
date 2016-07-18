// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacter.h"
#include "Skill.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillApplyEvent, USkill*, Skill, ABaseCharacter*, Character);

UENUM(BlueprintType)
enum class ESkillType : uint8 {
	ACTIVE UMETA(DisplayName = "Active"),
	PASSIVE UMETA(DisplayName = "Passive"),
	BUFF UMETA(DisplayName = "Buff"),
	CONJURATION UMETA(DisplayName = "Conjuration")
};

UENUM(BlueprintType)
enum class ESkillUsageType : uint8 {
	PROJECTILE UMETA(DisplayName = "Projectile"),
	TARGET UMETA(DisplayName = "Target"),
	AREA UMETA(DisplayName = "Area"),
	SELF UMETA(DisplayName = "Self"),
	PASSIVE UMETA(DisplayName = "Self")
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

USTRUCT(Blueprintable)
struct FSkillRequirements {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	uint8 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	UPlayerClass* Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TSubclassOf<USkill> ParentSkill;
};

UCLASS(Abstract, Blueprintable, BlueprintType, editinlinenew)
class FRAMEWORK_API USkill : public UObject {

	GENERATED_BODY()

public:
	USkill();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	FSkillRequirements Requirements;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	FString SkillName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	uint8 MaxLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	ESkillType Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	ESkillUsageType UsageType;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual bool CheckRequirements(ABaseCharacter* Character);

	UFUNCTION(Category = "Skill")
	virtual void BeginPlay();
};
