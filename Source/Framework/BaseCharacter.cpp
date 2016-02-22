// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Framework.h"
#include "BaseCharacter.h"
#include "Engine.h"
#include "EquipmentComponent.h"
#include "PlayerClass.h"
#include "Mage.h"
#include "Dodge.h"

//////////////////////////////////////////////////////////////////////////
// FActionList

FActionList::FActionList() {
	Dodge = NewObject<UDodge>();
}

//////////////////////////////////////////////////////////////////////////
// AFrameworkCharacter

ABaseCharacter::ABaseCharacter() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//TODO change it to choose it using Save
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(1, 1, -96.0), FRotator(0, -90, 0));
	}

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBlueprint(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP'"));
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

	// Load a player item container
	ItemEquipment = CreateDefaultSubobject<UEquipmentComponent>(TEXT("ItemContainer"));
	AddComponent(FName("ItemContainer"), false, FTransform(), ItemEquipment);
	ItemEquipment->bAutoActivate = true;

	//TODO load
	Health = 100;
	Action = FActionList();
}

USkill* ABaseCharacter::GetFireSkill() {
	return PlayerClass->GetSkill(FName(TEXT("FireBall")));
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABaseCharacter::BeginPlay() {
	//TODO load inventory
}

void ABaseCharacter::Tick(float DeltaSeconds) {
	//if (GetArmoryComponent()->Get(EInventoryContainerSlot::RIGHT_HAND)) {
	//	DrawDebugSphere(
	//		GetWorld(),
	//		GetArmoryComponent()->Get(EInventoryContainerSlot::RIGHT_HAND)->GetActorLocation(),
	//		30,
	//		32,
	//		FColor(255, 255, 0)
	//	);
	//}
	//if (GetArmoryComponent()->Get(EInventoryContainerSlot::LEFT_HAND)) {
	//	DrawDebugSphere(
	//		GetWorld(),
	//		GetArmoryComponent()->Get(EInventoryContainerSlot::LEFT_HAND)->GetActorLocation(),
	//		30,
	//		32,
	//		FColor(255, 0, 0)
	//	);
	//}
}

void ABaseCharacter::TakeDamage(AActor* DamageCauser, FHitResult Hit) {
	//Weapon.getDamage()
	//TODO add possibility to damage it using also skills and environment
	Health -= 10;
	if (Health <= 0) {
		Destroy();
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, TEXT("TakeDamage"));
}

//Redone those two!
void ABaseCharacter::Attack() {
	bIsAttackingRight = true;
}

void ABaseCharacter::AttackStop() {
	bIsAttackingRight = false;
}
