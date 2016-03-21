// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Item.h"
#include "InventoryComponent.generated.h"

UENUM(BlueprintType)
enum class EInventoryContainerSlot : uint8 {
	LEFT_HAND UMETA(DisplayName = "Left Hand"),
	RIGHT_HAND UMETA(DisplayName = "Right Hand"),
	HELMET UMETA(DisplayName = "Helmet"),
	CHESTPLATE UMETA(DisplayName = "Chestplate"),
	LEGGINGS UMETA(DisplayName = "Leggings"),
	BOOTS UMETA(DisplayName = "Boots")
};

USTRUCT()
struct FInventoryContainer {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	AWeapon* LeftHand;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	AWeapon* RightHand;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	AItem* Helmet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	AItem* Chestplate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	AItem* Leggings;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	AItem* Boots;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRAMEWORK_API UInventoryComponent : public UActorComponent {

	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TArray<AItem*> InventoryArray;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	FInventoryContainer& Container;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory")
	bool bHasItemsInRange;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	AWeapon* LeftHandItem;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	AWeapon* RightHandItem;

	//TODO delete it when the Inventory UI will be done
	UStaticMesh* StaticMeshLel;

public:	
	UInventoryComponent() : UInventoryComponent(FInventoryContainer()) {};
	UInventoryComponent(FInventoryContainer Load);

	virtual void OnRegister() override;

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void InitializeCollision(UShapeComponent* Shape);

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void InitializeInput(UInputComponent* Input);

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void OnComponentOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void OnComponentEndOverlap(class AActor * OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//////////////////////////////////////////////////////////////////////////
	// Equipment

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AItem* Get(EInventoryContainerSlot ItemSlot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsSet(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool Set(EInventoryContainerSlot ItemSlot, AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool Remove(EInventoryContainerSlot ItemSlot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryRemove(AItem* Item);

	//////////////////////////////////////////////////////////////////////////
	// Inventory

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Drop(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Clear();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AItem* GetItemByIndex(uint8 Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AItem* GetItemByID(uint8 ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<AItem*> GetItemsByType(EItemType ItemType);
};
