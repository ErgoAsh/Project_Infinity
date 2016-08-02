// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Effect.h"
#include "Useable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUseEvent, ABaseCharacter*, Character);

UENUM(BlueprintType)
enum class EUseableType : uint8 {
	FOOD,
	DRINK,
	SPECIAL
};

/**
 * 
 */
UCLASS(Blueprintable)
class FRAMEWORK_API AUseable : public AItem {

	GENERATED_BODY()

public:
	AUseable();

	//UPROPERTY(BlueprintAssignable, Category = "Item")
	FUseEvent UseEvent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	TArray<UEffect*> Effect;

	//TODO refactor Item.h structure, then think about this method
	//UFUNCTION(BlueprintCallable, Category = "Item")	
	//UAnimMontage* GetAnimation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
	void Use(ABaseCharacter* Character);
	void Use_Implementation(ABaseCharacter* Character);

	//BluprintImplementable?
};
