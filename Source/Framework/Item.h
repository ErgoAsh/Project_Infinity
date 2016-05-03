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
	ARMOR UMETA(DisplayName = "Armor"),
	MATERIAL UMETA(DisplayName = "Material"),
	TOOL UMETA(DisplayName = "Tool")
};

USTRUCT(Blueprintable) 
struct FItemType : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

	FItemType()
	  : Name(FName(TEXT("NULL"))),
		Type(0),
		Description(TEXT("DefaultItem")),
		CanStack(false),
		Damage(0),
		Durability(100) {};

	EItemType GetType() {
		switch (Type) {
		case 0: return EItemType::OTHER;
		case 1: return EItemType::USEABLE;
		case 2: return EItemType::WEAPON;
		case 3: return EItemType::ARMOR;
		case 4: return EItemType::MATERIAL;
		case 5: return EItemType::TOOL;
		default: return EItemType::OTHER;
		}
	}

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	uint8 ID;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	FName Name;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	uint8 Type;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	FString Description;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	FString Class;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	bool CanStack;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	uint8 Level;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	uint8 ItemType;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	float Damage;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	float Durability;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TAssetPtr<UTexture2D> Icon;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TAssetPtr<UStaticMesh> Model;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TAssetPtr<UAnimationAsset> Animation;

};

/**
 * 
 */
UCLASS()
class FRAMEWORK_API AItem : public AActor {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemType ItemData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	USphereComponent* Sphere;

public:
	AItem() : AItem(FItemType()) {};
	AItem(FItemType Data);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item")
	bool bPickAble = true;

	UFUNCTION(BlueprintCallable, Category = "Item")
	FItemType& GetItemData() { return ItemData; };

};
