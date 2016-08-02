// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FRAMEWORK_API AWeapon : public AItem {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Item")
	bool bUseDefaultTraceMethod;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	bool bCanTick;

protected:
	UFUNCTION(BlueprintCallable, Category = "Item")
	FHitResult Trace(const FVector& StartTrace, const FVector& EndTrace);

public:
	AWeapon();

// 	UFUNCTION(BlueprintCallable, Category = "Item") //TODO where to use?
// 	virtual void UseMain(class ABaseCharacter* BaseCharacter);
// 
// 	UFUNCTION(BlueprintCallable, Category = "Item")
// 	virtual void UseSecond(class ABaseCharacter* BaseCharacter);

	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	void SetCanTick(bool CanTick) { bCanTick = CanTick; }
};
