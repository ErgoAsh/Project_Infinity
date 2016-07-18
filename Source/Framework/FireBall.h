// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActiveSkill.h"
#include "FireBall.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FRAMEWORK_API UFireBall : public UActiveSkill {
	
	GENERATED_BODY()

public:
	UFireBall();

	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual void Execute(ABaseCharacter* Executor) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill")
	TAssetPtr<UStaticMesh> FireBallMesh;

	UPROPERTY(EditAnywhere, Category = "Skill")
	uint8 Damage;

};
