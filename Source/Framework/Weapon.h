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
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	bool bUseDefaultTraceMethod;

	AWeapon();

	UFUNCTION(BlueprintCallable, Category = "Item")
	FHitResult Trace(const FVector& StartTrace, const FVector& EndTrace);

	void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

};
