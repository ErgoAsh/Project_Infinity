// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Item.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRAMEWORK_API UInventoryComponent : public UActorComponent {

	GENERATED_BODY()

public:	
	UInventoryComponent();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory")
	TArray<AItem*> ItemsInRange;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory")
	bool bHasItemsInRange;

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void InitializeCollision(UShapeComponent* Shape);

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void InitializeInput(UInputComponent* Input);

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void OnComponentOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void OnComponentEndOverlap(class AActor * OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Pick up Item", Category = "Inventory")
	void PickUp(AItem* Item);

	//UFUNCTION(BlueprintCallable, WithValidation, Server, Reliable, Category = "Inventory")
	//virtual void Drop(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Clear();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(AItem* Item);

	AItem* GetItem(uint8 Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AItem* GetItem(EItemID ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<AItem*> GetItemsByType(EItemType ItemType);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TArray<AItem*> InventoryArray;

private:
	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "Inventory")
	void ConfirmPickUp();
};
