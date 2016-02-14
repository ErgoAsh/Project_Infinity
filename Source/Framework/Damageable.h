// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Damageable.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class UDamageable : public UInterface {

	GENERATED_UINTERFACE_BODY()

};

class FRAMEWORK_API IDamageable {

	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(Category = "Damage")
	virtual void TakeDamage(AActor* DamageCauser, FHitResult Hit);

};