// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Mage.h"
#include "FireBall.h"
#include "Engine.h"

void UMage::OnSkillExecute(ABaseCharacter* Caster) {
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, TEXT("MageOnSkill"));
}

void UMage::BeginPlay() {
	Super::BeginPlay();

	UFireBall* FireBall = NewObject<UFireBall>();
	FireBall->ExecuteEvent.AddDynamic(this, &UMage::OnSkillExecute);

	Skills.Add(FireBall);
}