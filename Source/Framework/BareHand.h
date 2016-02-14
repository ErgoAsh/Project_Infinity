// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Weapon.h"
#include "BareHand.generated.h"

/**
 * 
 */
UCLASS()
class FRAMEWORK_API ABareHand : public AWeapon {

	GENERATED_BODY()

public:
	ABareHand();
	
	UPROPERTY()
	USphereComponent* SphereCollision;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void DamageActors();

};
