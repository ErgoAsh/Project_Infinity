// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Engine.h"
#include "InventoryComponent.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	Clear();
}

TArray<AItem*> UInventoryComponent::GetItemsByType(EItemType ItemType) {
	TArray<AItem*> Items;
	for (int i = 0; i < InventoryArray.Num(); i++) {
		if (InventoryArray[i]->ItemType == ItemType) {
			Items.Add(InventoryArray[i]);
		}
	}
	return TArray<AItem*>();
}

AItem* UInventoryComponent::GetItem(EItemID ItemID) {
	for (int i = 0; i < InventoryArray.Num(); i++) {
		if (InventoryArray[i]->ItemID == ItemID) {
			return InventoryArray[i];
		}
	}
	return nullptr;
}

void UInventoryComponent::Clear() {
	for (AItem* Item : InventoryArray) {
		Item->Destroy();
		InventoryArray.Remove(Item);
	}
	InventoryArray.Empty();
}

AItem* UInventoryComponent::GetItem(uint8 Index) {
	return InventoryArray[Index];
}

void UInventoryComponent::AddItem(AItem* Item) {
	Item->SetOwner(GetOwner());
	InventoryArray.Add(Item);
}

bool UInventoryComponent::HasItem(AItem* Item) {
	return InventoryArray.Contains(Item);
}

void UInventoryComponent::InitializeCollision(UShapeComponent* Shape) {
	Shape->OnComponentBeginOverlap.AddDynamic(this, &UInventoryComponent::OnComponentOverlap);
	Shape->OnComponentEndOverlap.AddDynamic(this, &UInventoryComponent::OnComponentEndOverlap);
}

void UInventoryComponent::InitializeInput(UInputComponent* Input) {
	Input->BindAction("PickUp", IE_Pressed, this, &UInventoryComponent::ConfirmPickUp);
}

void UInventoryComponent::OnComponentOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherComp->GetCollisionProfileName().Compare(FName(TEXT("ItemPickUp"))), ESearchCase::IgnoreCase) {
		AItem* VisualItem = Cast<AItem>(OtherActor);
		if (VisualItem) {
			if (!(VisualItem->GetOwner() == GetOwner())) {
				ItemsInRange.Add(VisualItem);
				bHasItemsInRange = true;
			}
		}
	}
}

void UInventoryComponent::OnComponentEndOverlap(class AActor * OtherActor, 
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherComp->GetCollisionProfileName().Compare(FName(TEXT("ItemPickUp"))), ESearchCase::IgnoreCase) {
		AItem* VisualItem = Cast<AItem>(OtherActor);
		if (VisualItem) {
			ItemsInRange.Remove(VisualItem);
			bHasItemsInRange = false;
		}
	}
}

void UInventoryComponent::ConfirmPickUp() {
	for (int32 i = 0; i < ItemsInRange.Num(); i++) {
		if (!ItemsInRange[i]) continue;
		if (!ItemsInRange[i]->IsValidLowLevel()) continue;

		if (ItemsInRange[i]->Sphere->GetScaledSphereRadius() < GetOwner()->GetDistanceTo(ItemsInRange[i])) {
			AddItem(ItemsInRange[i]);
			ItemsInRange[i]->MeshComp->DestroyComponent();

			ACharacter* Character = Cast<ACharacter>(this->GetOwner());
			if (Character) {
				ItemsInRange[i]->OnUse(Character);
				PickUp(ItemsInRange[i]);
			}
		}
	}
}

//bool UInventoryComponent::PickUp_Validate(AItem* Item) {
//	//If inventory/slot is not full
//	return true;
//}
