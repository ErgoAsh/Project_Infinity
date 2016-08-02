// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8 {
	OTHER UMETA(DisplayName = "Other"),
	USEABLE UMETA(DisplayName = "Usable"),
	WEAPON UMETA(DisplayName = "Weapon"),
	CATALYST UMETA(DisplayName = "Catalyst"),
	ARMOR UMETA(DisplayName = "Armor"),
	MATERIAL UMETA(DisplayName = "Material"),
	TOOL UMETA(DisplayName = "Tool")
};

USTRUCT(Blueprintable)
struct FItemDamage : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

	FItemDamage()
	  : MaxCombo(3),
		Pierce(0),
		Slash(1),
		Blunt(0),
		Magic(0),
		Dark(0),
		Fire(0),
		Ice(0),
		Lightning(0),
		Mind(0),
		Poise(5),
		CriticalMultiplier(2),
		CounterMultiplier(1),
		Stability(100) {};

	UPROPERTY(VisibleAnywhere)
	uint8 MaxCombo;

	UPROPERTY(VisibleAnywhere)
	float Pierce;

	UPROPERTY(VisibleAnywhere)
	float Slash;

	UPROPERTY(VisibleAnywhere)
	float Blunt;

	UPROPERTY(VisibleAnywhere)
	float Magic;

	UPROPERTY(VisibleAnywhere)
	float Dark;

	UPROPERTY(VisibleAnywhere)
	float Fire;

	UPROPERTY(VisibleAnywhere)
	float Ice;

	UPROPERTY(VisibleAnywhere)
	float Lightning;

	UPROPERTY(VisibleAnywhere)
	float Mind;

	UPROPERTY(VisibleAnywhere)
	float Poise;

	UPROPERTY(VisibleAnywhere)
	float CriticalMultiplier;

	UPROPERTY(VisibleAnywhere)
	float CounterMultiplier;

	UPROPERTY(VisibleAnywhere)
	float BlockMultiplier;

	UPROPERTY(VisibleAnywhere)
	float Stability;
};

USTRUCT(Blueprintable)
struct FItemDefense : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

	FItemDefense()
	  : Piercing(0),
		Slash(0),
		Blunt(0),
		Magic(0),
		Dark(0),
		Fire(0),
		Ice(0),
		Lightning(0),
		Mind(0),
		Poise(5) {};

	UPROPERTY(VisibleAnywhere)
	uint8 MaxCombo;

	UPROPERTY(VisibleAnywhere)
	float Piercing;

	UPROPERTY(VisibleAnywhere)
	float Slash;

	UPROPERTY(VisibleAnywhere)
	float Blunt;

	UPROPERTY(VisibleAnywhere)
	float Magic;

	UPROPERTY(VisibleAnywhere)
	float Dark;

	UPROPERTY(VisibleAnywhere)
	float Fire;

	UPROPERTY(VisibleAnywhere)
	float Ice;

	UPROPERTY(VisibleAnywhere)
	float Lightning;

	UPROPERTY(VisibleAnywhere)
	float Mind;

	UPROPERTY(VisibleAnywhere)
	float Poise;
};

USTRUCT(Blueprintable) 
struct FItemData : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

	FItemData()
	  : ID(0),
		Name(FName(TEXT("NULL"))),
		Type(EItemType::OTHER),
		Class(FString(TEXT("ALL"))),
		Level(0),
		MaxDurability(100),
		MaxAmountPerStack(1),
		MaxStacksPerInventory(8),
		bCanStack(false),
		Description(TEXT("Default item, use with caution")) {};

	UPROPERTY(VisibleAnywhere)
	int32 ID;

	UPROPERTY(VisibleAnywhere)
	FName Name;

	UPROPERTY(VisibleAnywhere)
	EItemType Type;

	UPROPERTY(VisibleAnywhere)
	FString Class; //HACK FName?

	UPROPERTY(VisibleAnywhere)
	uint8 Level;

	UPROPERTY(VisibleAnywhere)
	float MaxDurability;
	
	UPROPERTY(VisibleAnywhere)
	uint8 MaxAmountPerStack;

	UPROPERTY(VisibleAnywhere)
	uint8 MaxStacksPerInventory;

	UPROPERTY(VisibleAnywhere)
	bool bCanStack;

	UPROPERTY(VisibleAnywhere)
	FString Description;

	UPROPERTY(VisibleAnywhere)
	TAssetPtr<UTexture2D> Icon;

	UPROPERTY(VisibleAnywhere)
	TAssetPtr<UStaticMesh> Model;

	UPROPERTY(VisibleAnywhere)
	TAssetPtr<UAnimMontage> MainAnim;

	UPROPERTY(VisibleAnywhere)
	TAssetPtr<UAnimMontage> SecondAnim;

	UPROPERTY(VisibleAnywhere)
	FItemDamage Damage;

	UPROPERTY(VisibleAnywhere)
	FItemDefense Defense;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FRAMEWORK_API AItem : public AActor {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Item")
	uint8 Amount = 1;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	bool bIsCollectable = true;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	int32 ID;

	UPROPERTY(EditAnywhere, Category = "Item")
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, Category = "Item")
	UStaticMeshComponent* MeshComp;

public:
	AItem();

	FItemData* GetItemData();

	UFUNCTION(BlueprintCallable, Category = "Item")
	uint8 GetAmount() { return Amount; }

	//TODO add network authority
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetAmount(uint8 NewAmount) { Amount = NewAmount; }

	UFUNCTION(BlueprintCallable, Category = "Item")
	void DestroyMesh() { MeshComp->DestroyComponent(false); } //HACK, or true?

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetMeshComponent(UStaticMeshComponent* Component) { MeshComp = Component; }

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool IsCollectable() const { return bIsCollectable; }

	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE int32 GetID() const { return ID; }
};
