// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Framework.h"
#include "BaseCharacter.h"
#include "Engine.h"
#include "PlayerClass.h"
#include "Mage.h"
#include "Dodge.h"
#include "Attack.h"

//////////////////////////////////////////////////////////////////////////
// FActionList

FActionList::FActionList() {
	Dodge = NewObject<UDodge>();
	Attack = NewObject<UAttack>();
}

//////////////////////////////////////////////////////////////////////////
// AFrameworkCharacter

ABaseCharacter::ABaseCharacter() : Action(FActionList()) {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//TODO change it to choose it using Save
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(1, 1, -96.0), FRotator(0, -90, 0));
	}

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBlueprint(TEXT("AnimBlueprint'/Game/ThirdPerson/AnimBlueprint.AnimBlueprint'"));
	if (AnimBlueprint.Object) {
		GetMesh()->SetAnimInstanceClass((UClass*) AnimBlueprint.Object->GeneratedClass);
	}

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
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

	Health = NewObject<UFrameworkAttribute>();
	Health->SetName()
	Mana = NewObject<UFrameworkAttribute>();
	Stamina = NewObject<UFrameworkAttribute>();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABaseCharacter::BeginPlay() {
	//TODO load inventory
}

void ABaseCharacter::Tick(float DeltaSeconds) {
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	//TODO add possibility to add/remove more damages using skills and environment

	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, TEXT("TakeDamage"));
	if (Health <= 0) {
		Destroy();
	}
}

float ABaseCharacter::InternalTakePointDamage(float Damage, FPointDamageEvent const& PointDamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	Health -= Damage;
	return Health;
}
