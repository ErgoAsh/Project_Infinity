// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Effect.h"
#include "Useable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUseEvent, ABaseCharacter*, Character);

/**
 * 
 */
UCLASS()
class FRAMEWORK_API AUseable : public AItem {//, public IEventContainer<FUseEvent> {

	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere, Category = "Item")
	//UAnimationAsset* Animation;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	UEffect* Effect;

public:
	AUseable();

	//TODO refactor Item.h structure, then think about this method
	//UFUNCTION(BlueprintCallable, Category = "Item")	
	//UAnimationAsset* GetAnimation();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, WithValidation, Category = "Item")
	void Use(ABaseCharacter* Character);
};
