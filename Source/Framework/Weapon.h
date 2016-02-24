// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class FRAMEWORK_API AWeapon : public AItem {

	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere, Category = "Item")
	//UAnimationAsset* Animation;

public:
	AWeapon();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item")
	bool bUseDefaultTraceMethod;

	UFUNCTION(BlueprintCallable, Category = "Item")
	FHitResult Trace(const FVector& StartTrace, const FVector& EndTrace);

	//UFUNCTION(BlueprintCallable, Category = "Item")	
	//UAnimationAsset* GetAnimation();

	void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

};
