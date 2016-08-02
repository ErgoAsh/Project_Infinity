// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Skill.h"
#include "Effect.h"
#include "PlayerClass.generated.h"

class ABaseCharacter;
static const FString Context = FString(TEXT("GENERAL"));

UENUM(BlueprintType)
enum class EClassType : uint8 {
	Fight,
	Heal,
	Support //TODO find better types
};

USTRUCT(Blueprintable)
struct FClassData : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere)
	uint8 Level;

	UPROPERTY(VisibleAnywhere)
	int32 XPToNextLevel;

	UPROPERTY(VisibleAnywhere)
	uint8 SkillPointsPerLevel;

	UPROPERTY(VisibleAnywhere)
	int32 MaxHealth;

	UPROPERTY(VisibleAnywhere)
	int32 MaxStamina;

	UPROPERTY(VisibleAnywhere)
	int32 MaxMana;

};

UCLASS(Abstract, Blueprintable, ClassGroup = "Character", meta = (BlueprintComponent))
class FRAMEWORK_API UPlayerClass : public UActorComponent {

	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class")
	UDataTable* Data;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Class")
	TArray<USkill*> Skills;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TArray<TSubclassOf<USkill>> SkillClasses;

	virtual void BeginPlay() override;

public:	
	UPlayerClass();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	FString ClassName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	UTexture* Icon;

	UPROPERTY(BlueprintReadWrite, Category = "Class")
	uint8 MaxLevel;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	USkill* GetSkill(FString Name);

	UFUNCTION(BlueprintCallable, Category = "Skill")
	TArray<USkill*> GetSkills();

	UFUNCTION(BlueprintCallable, Category = "Skill")
	int32 GetMaxHealth(uint8 Level);

	UFUNCTION(BlueprintCallable, Category = "Skill")
	int32 GetMaxStamina(uint8 Level);

	UFUNCTION(BlueprintCallable, Category = "Skill")
	int32 GetMaxMana(uint8 Level);
};