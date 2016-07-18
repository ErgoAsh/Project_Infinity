// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Skill.h"
#include "Effect.h"
#include "PlayerClass.generated.h"

class ABaseCharacter;

UENUM(BlueprintType)
enum class EClassType : uint8 {
	Fight,
	Heal,
	Support //TODO find better types
};

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = "Properties", meta = (BlueprintComponent))
class FRAMEWORK_API UPlayerClass : public UActorComponent {

	GENERATED_BODY()

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

	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Class")
	TArray<USkill*> Skills;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TArray<TSubclassOf<USkill>> SkillClasses;
};