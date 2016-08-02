// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Weapon.h"
#include "Item.h"
#include "InventoryComponent.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FEquipment {

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

UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class FRAMEWORK_API UInventoryComponent : public UActorComponent {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<AItem*> InventoryArray;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<AItem*> ItemsInRange;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	bool bHasItemsInRange;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	FEquipment Equipment;

protected:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AItem* GetItem(uint8 Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Clear();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveFromArray(uint8 Index);

	virtual void BeginPlay() override;
	virtual void OnRegister() override;

public:	
	UInventoryComponent() : UInventoryComponent(FEquipment()) {};
	UInventoryComponent(FEquipment Load);

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void InitializeCollision(UShapeComponent* Shape);

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void InitializeInput(UInputComponent* Shape);

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//////////////////////////////////////////////////////////////////////////
	// Equipment - override if more limbs

	/**
	 * @param Slot
	 *	1: Helmet
	 *	2: Chestplate
	 *	3: Leggings
	 *	4: Boots
	 *	5: Left hand
	 *	6: Right hand
	 * @returns item in specific slot
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual AItem* Get(uint8 Slot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual uint8 GetSlot(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool Set(uint8 Slot, AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool Remove(uint8 Slot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool TryRemove(AItem* Item);

	//////////////////////////////////////////////////////////////////////////
	// Inventory

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Drop(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PickUp();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<AItem*> GetItemsByID(uint8 ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<AItem*> GetItemsByType(EItemType ItemType);
};
