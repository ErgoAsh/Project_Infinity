// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Framework.h"
#include "BaseCharacter.h"
#include "Engine.h"
#include "PlayerClass.h"
#include "Dodge.h"
#include "DefaultAction.h"
#include "Attack.h"
#include "PassiveSkill.h"
#include "ActiveSkill.h"

//////////////////////////////////////////////////////////////////////////
// FActionList

FActionList::FActionList() {
	Dodge = NewObject<UDodge>();
	Attack = NewObject<UAttack>();
	DefaultAction = UDefaultAction::StaticClass()->GetDefaultObject<UDefaultAction>();
	CurrentAction = DefaultAction;
}

//////////////////////////////////////////////////////////////////////////
// AFrameworkCharacter

ABaseCharacter::ABaseCharacter() {
	//TODO Move to PlayerCharacter
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate (change it if is jumping)
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Load a player class
	if (*PClass != nullptr) {
		PlayerClass = (UPlayerClass*) CreateDefaultSubobject(TEXT("PlayerClass"), *PClass, *PClass, true, false, false);
		PlayerClass->bAutoActivate = true;
	}

	// Load a player inventory
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
	AddComponent(FName("PlayerInventory"), false, FTransform(), InventoryComponent);
	InventoryComponent->InitializeCollision(GetCapsuleComponent());
	InventoryComponent->bAutoActivate = true;

	Action = FActionList();

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
	PhysicalDefense = NewObject<UFrameworkAttribute>();
	PhysicalDefense->SetMinimumValue(-100);
	PhysicalDefense->SetMaximumValue(100);
	PhysicalDefense->SetBaseValue(0);
}

void ABaseCharacter::BeginPlay() {
	// Load a player class
	if (PlayerClass != nullptr && *PClass != nullptr) {
		PlayerClass = (UPlayerClass*) CreateDefaultSubobject(TEXT("PlayerClass"), *PClass, *PClass, true, false, false);
		PlayerClass->bAutoActivate = true;
	}

	if (PlayerClass) {
		for (USkill* Skill : PlayerClass->GetSkills()) {
			Skill->BeginPlay();

			UPassiveSkill* Passive = Cast<UPassiveSkill>(Skill);
			if (Passive) {
				Passive->Apply(this);
				continue;
			}
			UActiveSkill* Active = Cast<UActiveSkill>(Skill);
			if (Active) {
				Active->GetExecuteEvent()->Event.AddDynamic(this, &ABaseCharacter::ApplyAction);
				Active->GetExecuteEvent()->EndEvent.AddDynamic(this, &ABaseCharacter::UnApplyAction);
			}
		}
	}

	//TODO load inventory
	//TODO Or get it by some EntityDatabase or sth
	Super::BeginPlay();
}

void ABaseCharacter::ApplyAction(ABaseCharacter* BaseCharacter, TScriptInterface<IAction> ActionInterface) {
	Action.CurrentAction == ActionInterface;
	UActiveSkill* Active = Cast<UActiveSkill>(ActionInterface.GetObject());
	if (Active != nullptr) {
		ApplyEffects(Active->GetConsequences());
	}
}

void ABaseCharacter::UnApplyAction(ABaseCharacter* BaseCharacter, TScriptInterface<IAction> ActionInterface) {
	Action.CurrentAction == Action.DefaultAction;
}

void ABaseCharacter::Tick(float DeltaSeconds) {
	//TODO
}

void ABaseCharacter::UpdateEffects() {
	PhysicalDefense->ClearModifiers();
	Speed->ClearModifiers();
	MaxHealth->ClearModifiers();
	MaxMana->ClearModifiers();
	MaxStamina->ClearModifiers();
	for (UEffect* Effect : AppliedEffects) {
		if (Effect->GetEffectType() == EEffectType::BUFF || Effect->GetEffectType() == EEffectType::DEBUFF) {
			for (FModifier& Modifier : Effect->GetModifiers()) {
				//TODO change to if.else

				//switch (Effect->GetName()) { //What if there is multiple effects? We should stack but how?
				//case "Physical": PhysicalDefense->AddModifier(Modifier); 
				//case "Speed": Speed->AddModifier(Modifier);
				//case "Health": MaxHealth->AddModifier(Modifier);
				//case "Mana": MaxMana->AddModifier(Modifier);
				//case "Stamina": MaxStamina->AddModifier(Modifier);
				//case "Magic": //ADD to magic
				//case "Stamina_Regeneration": //ADD regeneration theard and attribute
				//}
			}
		}
	}
}

void ABaseCharacter::ApplyEffects(TArray<UEffect*> Effects) {
	AppliedEffects.Append(Effects);
	UpdateEffects();
}

void ABaseCharacter::ApplyEffect(UEffect* Effect) {
	AppliedEffects.Add(Effect);
	UpdateEffects();
}

void ABaseCharacter::RemoveEffect(UEffect* Effect) {
	AppliedEffects.Remove(Effect);
	UpdateEffects();
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	//TODO get somehow type (maybe FDamageEvent inheritance) of damage
	//if Magic (if both Magic & Phisical, make two TakeDamage occurances)
	
	//if Phisical
	Health = Health - (DamageAmount - DamageAmount * PhysicalDefense->GetValue());

	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, TEXT("TakeDamage"));
	if (Health <= 0) {
		bIsDead = true;
		GetMesh()->SetSimulatePhysics(true);
		//TODO delete AI if has any
		//TODO delete PlayerController
		//TODO add thread deleting mesh and rest in x time
	}
	return Health;
}

float ABaseCharacter::InternalTakePointDamage(float Damage, FPointDamageEvent const& PointDamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	return TakeDamage(Damage, PointDamageEvent, EventInstigator, DamageCauser);
	//Maybe it's not the right way...
	//Maybe use it just for headshots and blocking deflecting
}
 