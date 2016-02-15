// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUseEvent, ABaseCharacter*, Character);

/**
 * 
 */
UCLASS()
class FRAMEWORK_API AUseable : public AItem, public IEventContainer {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Item")
	UAnimationAsset* Animation;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FUseEvent UseEvent;

private:
	UFUNCTION(BlueprintCallable, Category = "Skill")
	void Use(ABaseCharacter* Character);

public:
	AUseable();

	UFUNCTION(BlueprintCallable, Category = "Item")	
	UAnimationAsset* GetAnimation();

	UFUNCTION(BlueprintCallable, Category = "Skill")
	TArray<TMulticastScriptDelegate*> GetEvents() override;

};
