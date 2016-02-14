// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Damageable.h"

UDamageable::UDamageable(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {

}

void IDamageable::TakeDamage(AActor* DamageCauser, FHitResult Hit) {

}