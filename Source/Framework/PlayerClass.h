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

UCLASS(Abstract, ClassGroup = "Properties", meta = (BlueprintComponent))
class FRAMEWORK_API UPlayerClass : public UActorComponent {

	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerClass();

	// Called when the game starts
	virtual void BeginPlay() override;

	//UFUNCTION(BlueprintCallable, Category = "Skill")
	//bool RegisterSkill(USkill* Skill);

	UFUNCTION(BlueprintCallable, Category = "Skill")
	USkill* GetSkill(FName Name);

	UFUNCTION(BlueprintCallable, Category = "Skill")
	TArray<USkill*> GetSkills();

	//Move to BaseCharacter instead?
	//UFUNCTION(BlueprintCallable, Category = "Effect")
	bool ApplyEffect(UEffect* Effect);

	//UFUNCTION(BlueprintCallable, Category = "Effect")
	bool RemoveEffect(UEffect* Effect);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Class")
	FText ClassName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	UTexture* Icon;

	UPROPERTY(BlueprintReadOnly, Category = "Class")
	uint8 MaxLevel;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TArray<USkill*> Skills;
};