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

USTRUCT(BlueprintType)
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

	//TODO TArray<TSubclassOf<IAction>> to add support for Blueprint?

	//Interact (NPC, special things)
	//PickUp

	FActionList();
};

UCLASS(Blueprintable, BlueprintType, config=Game)
class ABaseCharacter : public ACharacter {

	GENERATED_BODY()

	/** Inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

	/** Class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UPlayerClass* PlayerClass;

public:
	ABaseCharacter();

	//Should encapsulate these Properties?

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	bool bIsDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties") //TODO move max to PlayerClass
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
	UFrameworkAttribute* PhysicalDefense;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	TArray<UEffect*> AppliedEffects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	uint8 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FActionList Action;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void UpdateEffects();

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void ApplyEffects(TArray<UEffect*> Effects);

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void ApplyEffect(UEffect* Effect);

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void RemoveEffect(UEffect* Effect);

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	float InternalTakePointDamage(float Damage, FPointDamageEvent const& PointDamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	TSubclassOf<UPlayerClass> PClass;

private:
	UFUNCTION(Category = "Action")
	void ApplyAction(ABaseCharacter* BaseCharacter, TScriptInterface<IAction> ActionInterface);

	UFUNCTION(Category = "Action")
	void UnApplyAction(ABaseCharacter* BaseCharacter, TScriptInterface<IAction> ActionInterface);

public:
	/** Returns UInventoryComponent subobject **/
	FORCEINLINE class UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	/** Returns UPlayerClass subobject **/
	FORCEINLINE class UPlayerClass* GetPlayerClass() const { return PlayerClass; } //Delete?
};

