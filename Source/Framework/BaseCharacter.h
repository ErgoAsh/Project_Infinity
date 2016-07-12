// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "InventoryComponent.h"
#include "Loadable.h"
#include "ScriptInterface.h"
#include "FrameworkAttribute.h"
#include "Effect.h"
#include "BaseCharacter.generated.h"

class UPlayerClass;
class IAction;
class UDodge;
class UAttack;
class UDefaultAction;

USTRUCT()
struct FActionList {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	TScriptInterface<IAction> CurrentAction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	UDefaultAction* DefaultAction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	UDodge* Dodge;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	UAttack* Attack;

	//Interact (NPC, special things)
	//PickUp
	//Cast (Spell or Skill)

	FActionList();
};

UCLASS(Blueprintable, config=Game)
class ABaseCharacter : public ACharacter {

	GENERATED_BODY()

	/** Inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Properties, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

	/** Class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Properties, meta = (AllowPrivateAccess = "true"))
	class UPlayerClass* PlayerClass;

public:
	ABaseCharacter();

	//Should encapsulate these Properties?

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	bool bIsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	UFrameworkAttribute* MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	int32 Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	UFrameworkAttribute* MaxMana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	int32 Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	UFrameworkAttribute* MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	int32 Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	UFrameworkAttribute* Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	UFrameworkAttribute* PhisicalDefense;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	TArray<UEffect*> AppliedEffects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	uint8 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FActionList Action;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	float InternalTakePointDamage(float Damage, FPointDamageEvent const& PointDamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

public:
	/** Returns UInventoryComponent subobject **/
	FORCEINLINE class UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	/** Returns UPlayerClass subobject **/
	FORCEINLINE class UPlayerClass* GetPlayerClass() const { return PlayerClass; }
};

