// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Framework.h"
#include "BaseCharacter.h"
#include "Engine.h"
#include "PlayerClass.h"
#include "Mage.h"
#include "Dodge.h"
#include "DefaultAction.h"
#include "Attack.h"

//////////////////////////////////////////////////////////////////////////
// FActionList

FActionList::FActionList() {
	Dodge = NewObject<UDodge>();
	Attack = NewObject<UAttack>();
	DefaultAction = UDefaultAction::StaticClass()->GetDefaultObject<UDefaultAction>();
}

//////////////////////////////////////////////////////////////////////////
// AFrameworkCharacter

ABaseCharacter::ABaseCharacter() : Action(FActionList()) {
	//TODO Move to PlayerCharacter
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//TODO change it to choose it using Save&Load
	//TODO move to PlayerCharacter!
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(1, 1, -96.0), FRotator(0, -90, 0));
	}

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBlueprint(TEXT("AnimBlueprint'/Game/Mannequin/Animations/AnimBlueprint.AnimBlueprint'"));
	if (AnimBlueprint.Object) {
		GetMesh()->SetAnimInstanceClass((UClass*) AnimBlueprint.Object->GeneratedClass);
	}

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate (change it if is jumping)
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Load a player class
	PlayerClass = CreateDefaultSubobject<UMage>(TEXT("PlayerClass"));
	PlayerClass->bAutoActivate = true;

	// Load a player inventory
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
	AddComponent(FName("PlayerInventory"), false, FTransform(), InventoryComponent);
	InventoryComponent->InitializeCollision(GetCapsuleComponent());
	InventoryComponent->bAutoActivate = true;

	// Load a player variables
	MaxHealth = NewObject<UFrameworkAttribute>();
	MaxHealth->SetMinimumValue(1);
	MaxHealth->SetBaseValue(100);

	MaxMana = NewObject<UFrameworkAttribute>();
	MaxMana->SetMinimumValue(1);
	MaxMana->SetBaseValue(100);

	MaxStamina = NewObject<UFrameworkAttribute>();
	MaxStamina->SetMinimumValue(1);
	MaxStamina->SetBaseValue(100);

	Speed = NewObject<UFrameworkAttribute>();
	Speed->SetMinimumValue(0);
	Speed->SetBaseValue(100);

	//Phisical defense
	//Elemental defense should be also added, I think
	//Need to add distinguish between TakeDamage types
	PhisicalDefense = NewObject<UFrameworkAttribute>();
	PhisicalDefense->SetMinimumValue(-100);
	PhisicalDefense->SetMaximumValue(100);
	PhisicalDefense->SetBaseValue(0);
}

void ABaseCharacter::BeginPlay() {
	//TODO load inventory
	//TODO Or get it by some EntityDatabase or sth
}

void ABaseCharacter::Tick(float DeltaSeconds) {
	//TODO move it somewhere else
	//for (UEffect* Effect : AppliedEffects) {
	//	if (Effect->GetEffectType() == BUFF || Effect->GetEffectType() == DEBUFF) {
	//		for (FModifier Modifier : Effect->GetModifiers())
	//
	//			switch (Effect->GetName()) {
	//				case "Phisical": PhisicalDefense->AddModifier(Modifier)
	//				case "Magic": //ADD to magic
	//			}
	//		}
	//	}
	//}
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	//TODO get somehow type (maybe FDamageEvent inheritance) of damage
	//if Magic (if both Magic & Phisical, make two TakeDamage occurances)
	
	//if Phisical
	Health = Health - (DamageAmount - DamageAmount * PhisicalDefense->GetValue());

	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, TEXT("TakeDamage"));
	if (Health <= 0) {
		bIsDead = true;
		GetMesh()->SetSimulatePhysics(true);
		//TODO delete AI if has any
		//TODO delete PlayerController
	}
	return Health;
}

float ABaseCharacter::InternalTakePointDamage(float Damage, FPointDamageEvent const& PointDamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	return TakeDamage(Damage, PointDamageEvent, EventInstigator, DamageCauser);
	//Maybe it's not the right way...
	//Maybe use it just for headshots and blocking deflecting
}
 