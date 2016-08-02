// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Action.h"
#include "Dodge.generated.h"


class ABaseCharacter;

/**
 * 
 */
UCLASS(Blueprintable)
class FRAMEWORK_API UDodge : public UObject, public IAction {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Action")
	UEventContainer* ExecuteEvent;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Action")
	TAssetPtr<UAnimMontage> Animation;

public:
	UDodge();

	UFUNCTION(BlueprintCallable, Category = "Action")
	UAnimMontage* GetAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Execute(ABaseCharacter* Executor) override;

	UFUNCTION(BlueprintCallable, Category = "Event")
	UEventContainer* GetExecuteEvent() override;

};
