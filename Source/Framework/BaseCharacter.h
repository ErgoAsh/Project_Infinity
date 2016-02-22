// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "InventoryComponent.h"
#include "EquipmentComponent.h"
#include "Damageable.h"
#include "ScriptInterface.h"
#include "BaseCharacter.generated.h"

class UPlayerClass;
class IAction;
class UDodge;

USTRUCT()
struct FActionList {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	TScriptInterface<IAction> CurrentAction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	UDodge* Dodge;
	//InteractWithObj
	//InteractWithNPC
	//PickUpItem

	//HandLeft
	//HandLeftSpecial
	//HandRight
	//HandRightSpecial

	FActionList();
};

UCLASS(config=Game)
class ABaseCharacter : public ACharacter, public IDamageable {

	GENERATED_BODY()
	
protected:
	/** Inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Properties, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

	/** Player class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Properties, meta = (AllowPrivateAccess = "true"))
	class UPlayerClass* PlayerClass;

	/** Player armory */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Properties, meta = (AllowPrivateAccess = "true"))
	class UEquipmentComponent* ItemEquipment;

public:
	ABaseCharacter();

	UFUNCTION(BlueprintCallable, Category = "Skill")
	USkill* GetFireSkill();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
	bool bIsAttackingLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
	bool bIsAttackingRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
	bool bIsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
	uint8 Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
	uint8 Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
	uint8 Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
	FActionList Action;

	UFUNCTION(Category = "Damage")
	void TakeDamage(AActor* DamageCauser, FHitResult Hit) override;

	//TODO GetInventoryPlacement(?), GetCurrentWeapon(), GetWeaponAttackAnimation();
	//TODO AttackLeft, AttackRight
	void Attack();
	void AttackStop();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

public:
	/** Returns UInventoryComponent subobject **/
	FORCEINLINE class UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	/** Returns PlayerClass subobject **/
	FORCEINLINE class UPlayerClass* GetPlayerClass() const { return PlayerClass; }
	/** Returns ArmoryComponent subobject **/
	FORCEINLINE class UEquipmentComponent* GetEquipmentComponent() const { return ItemEquipment; }
};

