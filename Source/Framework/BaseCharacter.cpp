// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Framework.h"
#include "FrameworkGameInstance.h"
#include "BaseCharacter.h"
#include "Engine.h"
#include "PlayerClass.h"
#include "Dodge.h"
#include "DefaultAction.h"
#include "Attack.h"
#include "PassiveSkill.h"
#include "ActiveSkill.h"
#include "InventoryComponent.h"
#include "DefenseComponent.h"
#include "VisualEffect.h"

ABaseCharacter::ABaseCharacter() {
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//TODO move to APlayerCharacter?
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

	// Load hands collision
	LeftHand = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHand"));
	LeftHand->SetSphereRadius(35.0f);
	LeftHand->SetupAttachment(GetMesh(), TEXT("WeaponSocketL"));
	LeftHand->BodyInstance.SetCollisionProfileName("OverlapAll");
	LeftHand->OnComponentHit.AddDynamic(this, &ABaseCharacter::OnHit);

	RightHand = CreateDefaultSubobject<USphereComponent>(TEXT("RightHand"));
	RightHand->SetSphereRadius(35.0f);
	RightHand->SetupAttachment(GetMesh(), TEXT("WeaponSocketR"));
	RightHand->BodyInstance.SetCollisionProfileName("OverlapAll");
	RightHand->OnComponentHit.AddDynamic(this, &ABaseCharacter::OnHit);

	// Load a player inventory
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
	AddComponent(FName("PlayerInventory"), false, FTransform(), InventoryComponent);
	InventoryComponent->InitializeCollision(GetCapsuleComponent());
	InventoryComponent->bAutoActivate = true;

	// Load a player variables
	AdditionalMaxHealth = NewObject<UFrameworkAttribute>();
	AdditionalMaxHealth->SetMinimumValue(1);
	AdditionalMaxHealth->SetBaseValue(100);

	AdditionalMaxMana = NewObject<UFrameworkAttribute>();
	AdditionalMaxMana->SetMinimumValue(1);
	AdditionalMaxMana->SetBaseValue(100);

	AdditionalMaxStamina = NewObject<UFrameworkAttribute>();
	AdditionalMaxStamina->SetMinimumValue(1);
	AdditionalMaxStamina->SetBaseValue(100);
}

void ABaseCharacter::SetCurrentAction(TScriptInterface<IAction> Action) {
	CurrentAction = Action;
}

void ABaseCharacter::SetDefaultAction() {
	CurrentAction.SetObject(DefaultAction);
}

float ABaseCharacter::GetCooldown(USkill* Skill) {
	if (SkillCooldowns.Contains(Skill)) {
		return *SkillCooldowns.Find(Skill);
	} else {
		return -1;
	}
}

void ABaseCharacter::BeginPlay() {
	Super::BeginPlay();
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

	if (GetGameInstance() == nullptr) {
		UE_LOG(Debugg, Error, TEXT("[ABaseCharacter::ABaseCharacter] Normal GameInstance is null"));
		return;
	} else {
		UFrameworkGameInstance* GameInstance = Cast<UFrameworkGameInstance>(GetGameInstance());
		if (GameInstance) {
			GameInstance->GetStreamableManager().SimpleAsyncLoad(DefaultAttackMontage.ToStringReference());
		} else {
			UE_LOG(Debugg, Error, TEXT("[ABaseCharacter::ABaseCharacter] FrameworkGameInstance is null"));
		}
	}

	if (Dodge == nullptr)
		UE_LOG(Debugg, Warning, TEXT("[ABaseCharacter::BeginPlay] Action.Dodge is null"));
	if (DefaultAction == nullptr)
		UE_LOG(Debugg, Warning, TEXT("[ABaseCharacter::BeginPlay] Action.DefaultAction is null"));
	if (CurrentAction == nullptr)
		UE_LOG(Debugg, Warning, TEXT("[ABaseCharacter::BeginPlay] Action.CurrentAction is null"));

	if (GetMesh()->GetAnimInstance() != nullptr) {
		UFrameworkAnimInstance* AnimInstance = Cast<UFrameworkAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance != nullptr) {
			if (Attack == nullptr) {
				UE_LOG(Debugg, Warning, TEXT("[ABaseCharacter::BeginPlay] Action.Attack is null"));
				return;
			}
			Attack->GetExecuteEvent()->EndEvent.AddDynamic(AnimInstance, &UFrameworkAnimInstance::SetDefaultMontage);
		}
	} else {
		UE_LOG(Debugg, Warning, TEXT("[ABaseCharacter::BeginPlay] AnimInstance is null"));
	}

	//TODO load inventory
	//TODO Or get it by some EntityDatabase or sth
}

void ABaseCharacter::ApplyAction(ABaseCharacter* BaseCharacter, TScriptInterface<IAction> ActionInterface) {
	CurrentAction == ActionInterface;
	UActiveSkill* Active = Cast<UActiveSkill>(ActionInterface.GetObject());
	if (Active != nullptr) {
		ApplyEffects(Active->GetConsequences());
	}
}

void ABaseCharacter::UnApplyAction(ABaseCharacter* BaseCharacter, TScriptInterface<IAction> ActionInterface) {
	SetDefaultAction();
}

void ABaseCharacter::PostInitProperties() {
	Super::PostInitProperties();

	Dodge = NewObject<UDodge>();
	Attack = NewObject<UAttack>();
	DefaultAction = UDefaultAction::StaticClass()->GetDefaultObject<UDefaultAction>();
	CurrentAction.SetObject(DefaultAction);
}

void ABaseCharacter::BeginAction(uint8 Slot, bool bIsMain) {
	UFrameworkAnimInstance* AnimInstance = Cast<UFrameworkAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance != nullptr) {
		uint8 MaxCombo = 1;
		AItem* Item = InventoryComponent->Get(Slot);
		if (Item == nullptr) {
			UAnimMontage* Montage = DefaultAttackMontage.Get();
			if (Montage == nullptr) {
				UE_LOG(Debugg, Warning, TEXT("ABaseCharacter::BeginAction: Default montage is NULL"));
				return;
			} else {
				Attack->HoldedWeapon = nullptr;
				Attack->Montage = Montage;
				MaxCombo = 2;
			}
		} else {
			AWeapon* W = Cast<AWeapon>(Item);
			Attack->HoldedWeapon = W;
			FItemData* Data = Item->GetItemData();
			if (Data) {
				if (bIsMain) {
					Attack->Montage = Data->MainAnim.Get();
				} else {
					Attack->Montage = Data->SecondAnim.Get();
				}
				MaxCombo = Data->Damage.MaxCombo;
			}
		}
		if (Attack != nullptr) {
			if (!AnimInstance->Montage_IsPlaying(Attack->Montage)) {
				Attack->Execute(this);
			}
			AnimInstance->Attack(Attack->Montage, Slot, MaxCombo, Attack);
		} else {
			UE_LOG(Debugg, Error, TEXT("[ABaseCharacter::BeginAttack] Attack is null"));
			return;
		}
	} else {
		UE_LOG(Debugg, Warning, TEXT("[ABaseCharacter::BeginAttack] AnimInstance is null"));
	}
}

void ABaseCharacter::Tick(float DeltaSeconds) {
	//TODO
}

float ABaseCharacter::GetMaxHealth() { 
	return PlayerClass->GetMaxHealth(Level) + AdditionalMaxHealth->GetValue(); 
}

float ABaseCharacter::GetMaxStamina() {
	return PlayerClass->GetMaxStamina(Level) + AdditionalMaxStamina->GetValue();
}

float ABaseCharacter::GetMaxMana() {
	return PlayerClass->GetMaxMana(Level) + AdditionalMaxMana->GetValue();
}

void ABaseCharacter::UpdateEffects() {
	DefenseComponent->ClearModifiers();
	AdditionalMaxHealth->ClearModifiers();
	AdditionalMaxMana->ClearModifiers();
	AdditionalMaxStamina->ClearModifiers();
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
	for (UEffect* Effect : Effects) {
		AppliedEffects.Add(Effect);
		UVisualEffect* Visual = Cast<UVisualEffect>(Effect);
		if (Visual != nullptr) {
			Visual->Execute();
		}
	}
	UpdateEffects();
}

void ABaseCharacter::ApplyEffect(UEffect* Effect) {
	AppliedEffects.Add(Effect);
	UVisualEffect* Visual = Cast<UVisualEffect>(Effect);
	if (Visual != nullptr) {
		Visual->Execute();
	}
	UpdateEffects();
}

void ABaseCharacter::RemoveEffect(UEffect* Effect) {
	AppliedEffects.Remove(Effect);
	UpdateEffects();
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	AWeapon* Weapon = Cast<AWeapon>(DamageCauser);
	if (Weapon != nullptr) {
		FItemData* ItemData = Weapon->GetItemData();
		if (ItemData) { //TODO add bonuses from UEffects, headshots and shield deflecting
			float SummaryDamage = (DefenseComponent->Dark->GetValue() - ItemData->Damage.Dark)
				+ (DefenseComponent->Fire->GetValue() - ItemData->Damage.Fire)
				+ (DefenseComponent->Lightning->GetValue() - ItemData->Damage.Lightning)
				+ (DefenseComponent->Ice->GetValue() - ItemData->Damage.Ice)
				+ (DefenseComponent->Magic->GetValue() - ItemData->Damage.Magic)
				+ (DefenseComponent->Mind->GetValue() - ItemData->Damage.Mind)
				+ (DefenseComponent->Pierce->GetValue() - ItemData->Damage.Pierce)
				+ (DefenseComponent->Blunt->GetValue() - ItemData->Damage.Blunt)
				+ (DefenseComponent->Slash->GetValue() - ItemData->Damage.Slash);
			Health -= SummaryDamage;
		}
		Health -= DamageAmount;
	} else {
		Health -= DamageAmount;
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, TEXT("TakeDamage"));
	if (Health <= 0) {
		bIsDead = true;
		GetMesh()->SetSimulatePhysics(true);
		//TODO delete AI if has any
		//TODO delete PlayerController
		//TODO add thread deleting mesh
	}
	return Health;
}

float ABaseCharacter::InternalTakePointDamage(float Damage, FPointDamageEvent const& PointDamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	//TODO if headshot/shield block - change UDamageType
	return TakeDamage(Damage, PointDamageEvent, EventInstigator, DamageCauser);
}


void ABaseCharacter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherComp == LeftHand || OtherComp == RightHand
		|| OtherActor == GetOwner() || OtherActor->GetOwner() == GetOwner()) return;
	
	USphereComponent* Hand;
	if (HitComp == LeftHand) {
		Hand = LeftHand;
	} else if (HitComp == RightHand) { 
		Hand = RightHand; 
	} else return;

	ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor);
	if (Character) {
		ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
		if (OwnerCharacter) {
			Character->TakeDamage(5, FDamageEvent(), OwnerCharacter->GetController(), this);
		}
	}
	ADestructibleActor* Destructible = Cast<ADestructibleActor>(OtherActor);
	if (Destructible) {
		FVector Self = GetTransform().GetTranslation();
		FVector Other = OtherActor->GetTransform().GetTranslation();
		if (Destructible->bCanBeDamaged) {
			Destructible->GetDestructibleComponent()-> //TODO check HitResult vectors
				ApplyDamage(100, GetActorLocation(), (Hit.ImpactPoint - GetActorLocation()) * -1, 2500);
		}
	}
}
