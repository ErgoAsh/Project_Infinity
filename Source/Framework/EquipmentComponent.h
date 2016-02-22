// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "BareHand.h"
#include "EquipmentComponent.generated.h"

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
	AItem* LeftHand;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	AItem* RightHand;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	AItem* Helmet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	AItem* Chestplate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	AItem* Leggings;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	AItem* Boots;

};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FRAMEWORK_API UEquipmentComponent : public UActorComponent {

	GENERATED_BODY()
		
public:	
	// Sets default values for this component's properties
	UEquipmentComponent() : UEquipmentComponent(FInventoryContainer()) {};
	UEquipmentComponent(FInventoryContainer Load);

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnRegister() override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AItem* Get(EInventoryContainerSlot ItemSlot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool Set(EInventoryContainerSlot ItemSlot, AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool Remove(EInventoryContainerSlot ItemSlot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryRemove(AItem* Item);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	FInventoryContainer Container;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	AWeapon* LeftHandItem;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	AWeapon* RightHandItem;

	UStaticMesh* StaticMeshLel;
};
