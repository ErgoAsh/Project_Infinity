// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "ScriptInterface.h"
#include "FrameworkAttribute.h"
#include "BaseCharacter.generated.h"

class UPlayerClass;
class IAction;
class UDodge;
class UAttack;
class UDefaultAction;
class UActiveSkill;

UCLASS(Blueprintable, BlueprintType, config=Game)
class ABaseCharacter : public ACharacter {

	GENERATED_BODY()

	//////////////////////////////////////////////////////////////////////////
	// Properties

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	float Health;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	float Stamina;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	float Mana;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	USphereComponent* LeftHand;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	USphereComponent* RightHand;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	bool bIsDead = false;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	TMap<class USkill*, float> SkillCooldowns;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	UActiveSkill* CurrentSkill; //TODO rename?

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	TArray<class UEffect*> AppliedEffects;

	UPROPERTY(VisibleAnywhere, Category = "Action")
	TScriptInterface<IAction> CurrentAction;

	UPROPERTY(VisibleAnywhere, Category = "Action")
	bool bCanUseNextAction = true;

protected:
	//////////////////////////////////////////////////////////////////////////
	// Components

	/** Inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

	/** Damage */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UDefenseComponent* DefenseComponent;

	/** Class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UPlayerClass* PlayerClass;

	//////////////////////////////////////////////////////////////////////////
	// Misc

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	TSubclassOf<UPlayerClass> PClass;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	TAssetPtr<UAnimMontage> DefaultAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	uint8 Level;

	virtual void PostInitProperties() override;
	virtual void BeginAction(uint8 Slot, bool bIsMain);
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

public:
	ABaseCharacter();

	//////////////////////////////////////////////////////////////////////////
	// Actions

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	UDefaultAction* DefaultAction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	UDodge* Dodge;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill")
	UAttack* Attack;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetCurrentAction(TScriptInterface<IAction> Action);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetDefaultAction();

	UFUNCTION(BlueprintCallable, Category = "Properties")
	float GetCooldown(USkill* Skill);

	//////////////////////////////////////////////////////////////////////////
	// Attributes

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	UFrameworkAttribute* AdditionalMaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	UFrameworkAttribute* AdditionalMaxStamina;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	UFrameworkAttribute* AdditionalMaxMana;

	UFUNCTION(BlueprintCallable, Category = "Properties")
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Properties")
	float GetMaxStamina();

	UFUNCTION(BlueprintCallable, Category = "Properties")
	float GetMaxMana();

	//////////////////////////////////////////////////////////////////////////
	// Effects

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void UpdateEffects();

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void ApplyEffects(TArray<class UEffect*> Effects);

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void ApplyEffect(class UEffect* Effect);

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void RemoveEffect(class UEffect* Effect);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void ApplyAction(ABaseCharacter* BaseCharacter, TScriptInterface<IAction> ActionInterface);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void UnApplyAction(ABaseCharacter* BaseCharacter, TScriptInterface<IAction> ActionInterface);

	//////////////////////////////////////////////////////////////////////////
	// Damage

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	float InternalTakePointDamage(float Damage, FPointDamageEvent const& PointDamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	/** Returns UInventoryComponent subobject **/
	FORCEINLINE class UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	/** Returns UPlayerClass subobject **/
	FORCEINLINE class UPlayerClass* GetPlayerClass() const { return PlayerClass; }
	/** Returns UDamageComponent subobject **/
	FORCEINLINE class UDefenseComponent* GetDefenseComponent() const { return DefenseComponent; }
	/** Returns Character's level **/
	FORCEINLINE uint8 GetLevel() const { return Level; }
	/** Returns applied Effects **/
	FORCEINLINE TArray<class UEffect*> GetEffects() { return AppliedEffects; }
	/** Returns current using Action **/
	FORCEINLINE TScriptInterface<IAction> GetCurrentAction() { return CurrentAction; }

	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMana() const { return Mana; }
	FORCEINLINE float GetStamina() const { return Stamina; }
};

