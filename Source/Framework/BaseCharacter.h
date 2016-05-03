// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "InventoryComponent.h"
#include "Loadable.h"
#include "ScriptInterface.h"
#include "FrameworkAttribute.h"
#include "BaseCharacter.generated.h"

class UPlayerClass;
class IAction;
class UDodge;
class UAttack;

USTRUCT()
struct FActionList {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	TScriptInterface<IAction> CurrentAction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	UDodge* Dodge;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	UAttack* Attack;
	//InteractWithNPC
	//PickUpItem

	FActionList();
};

UCLASS(config=Game)
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
	bool bIsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
	UFrameworkAttribute* Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
	UFrameworkAttribute* Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
	UFrameworkAttribute* Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BB")
	FActionList& Action;

	UFUNCTION(Category = "Damage")
	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(Category = "Damage")
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

