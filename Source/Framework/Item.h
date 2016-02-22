// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8 {
	WEAPON, //UMETA(DisplayName = "Weapon"),
	ARMOR,  //UMETA(DisplayName = "Armor"),
	USEABLE //UMETA(DisplayName = "Usable")
};

UENUM(BlueprintType)
enum class EItemID : uint8 {
	BARE_HANDS, //UMETA(DisplayName = "Bare Hands"),
	SWORD_TEST  //UMETA(DisplayName = "Test Sword")
};

USTRUCT()
struct FItemData : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

public:
	//TODO add attributes as the last argument
	FItemData() 
	  : Name(FName(TEXT("BARE_HAND"))), 
		Type(0), 
		Description(TEXT("This land is peaceful")), 
		CanStack(true), 
		Damage(10) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	uint8 Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool CanStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	uint8 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TAssetPtr<UTexture> Icon;
};

/**
 * 
 */
UCLASS()
class FRAMEWORK_API AItem : public AActor {
	GENERATED_BODY()
	
public:
	AItem() : AItem(EItemID::BARE_HANDS, EItemType::WEAPON) {};
	AItem(EItemID ID, EItemType Type);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item")
	EItemID ItemID; //DELETE

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item")
	EItemType ItemType = EItemType::WEAPON;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	FString DisplayName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	FString Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	bool bCanStack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	bool bUse; //Move it to Usable

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	uint8 Amount = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	USphereComponent* Sphere;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	UTexture* Icon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	USphereComponent* Sphere;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Actor")
	UStaticMeshComponent* MeshComp;

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Item: Used")
	bool OnUse(ACharacter* character);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Item: Dropped")
	bool OnDrop(ACharacter* character);

};
