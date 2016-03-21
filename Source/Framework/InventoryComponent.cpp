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

void UEquipmentComponent::OnRegister() {
	Super::OnRegister();


	ABaseCharacter* Char = Cast<ABaseCharacter>(GetOwner());
	if (Char) {
		if (!RightHandItem) {
			RightHandItem = (AWeapon*)GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass());
			RightHandItem->SetOwner(GetOwner());
			RightHandItem->MeshComp->StaticMesh = StaticMeshLel;
			RightHandItem->bUseDefaultTraceMethod = true;
			RightHandItem->GetRootComponent()->AttachTo(Char->GetMesh(), TEXT("WeaponSocketR"),
				EAttachLocation::SnapToTargetIncludingScale, true);
		}
		Container.RightHand = RightHandItem;
		RightHandItem->MeshComp->BodyInstance.SetCollisionProfileName("OverlapAll");
		//RightHandItem->MeshComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);

		if (!LeftHandItem) {
			LeftHandItem = (AWeapon*)GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass());
			LeftHandItem->SetOwner(GetOwner());
			LeftHandItem->MeshComp->StaticMesh = StaticMeshLel;
			LeftHandItem->bUseDefaultTraceMethod = true;
			LeftHandItem->GetRootComponent()->AttachTo(Char->GetMesh(), TEXT("WeaponSocketL"),
				EAttachLocation::SnapToTargetIncludingScale, true);
		}
		Container.LeftHand = LeftHandItem;
		LeftHandItem->MeshComp->BodyInstance.SetCollisionProfileName("OverlapAll");
		//LeftHandItem->MeshComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	}
}

AItem* UEquipmentComponent::Get(EInventoryContainerSlot ItemSlot) {
	switch (ItemSlot) {
	case EInventoryContainerSlot::LEFT_HAND:
		return Container.LeftHand;
	case EInventoryContainerSlot::RIGHT_HAND:
		return Container.RightHand;
	case EInventoryContainerSlot::HELMET:
		return Container.Helmet;
	case EInventoryContainerSlot::CHESTPLATE:
		return Container.Chestplate;
	case EInventoryContainerSlot::LEGGINGS:
		return Container.Leggings;
	case EInventoryContainerSlot::BOOTS:
		return Container.Boots;
	default:
		return nullptr;
	}
}

bool UEquipmentComponent::Set(EInventoryContainerSlot ItemSlot, AItem* Item) {
	if (!Item) {
		return false;
	}
	ABaseCharacter* Char = Cast<ABaseCharacter>(GetOwner());
	if (Char) {
		UInventoryComponent* Inventory = Char->GetInventoryComponent();
		if (Inventory && (Inventory->HasItem(Item) || (Item == LeftHandItem || Item == RightHandItem))) {
			//If can use
			switch (ItemSlot) {
			case EInventoryContainerSlot::RIGHT_HAND:
				Container.RightHand = Item;
				Item->GetRootComponent()->AttachTo(Char->GetMesh(), TEXT("WeaponSocketR"),
					EAttachLocation::SnapToTargetIncludingScale, true);
				return true;

			case EInventoryContainerSlot::LEFT_HAND:
				Container.LeftHand = Item;
				Item->GetRootComponent()->AttachTo(Char->GetMesh(), TEXT("WeaponSocketL"),
					EAttachLocation::SnapToTargetIncludingScale, true);
				return true;

			case EInventoryContainerSlot::HELMET:
				Container.Helmet = Item;
				return true;

			case EInventoryContainerSlot::CHESTPLATE:
				Container.Chestplate = Item;
				return true;

			case EInventoryContainerSlot::LEGGINGS:
				Container.Leggings = Item;
				return true;

			case EInventoryContainerSlot::BOOTS:
				Container.Boots = Item;
				return true;
			default: break;
			}
		}
	}
	return false;
}

bool UEquipmentComponent::Remove(EInventoryContainerSlot ItemSlot) {
	switch (ItemSlot) {
	case EInventoryContainerSlot::LEFT_HAND:
		if (Container.LeftHand) {
			Container.LeftHand = LeftHandItem;
			return true;
		} break;
	case EInventoryContainerSlot::RIGHT_HAND:
		if (Container.RightHand) {
			Container.RightHand = RightHandItem;
			return true;
		} break;
	case EInventoryContainerSlot::HELMET:
		if (Container.Helmet) {
			Container.Helmet = nullptr;
			return true;
		} break;
	case EInventoryContainerSlot::CHESTPLATE:
		if (Container.Chestplate) {
			Container.Chestplate = nullptr;
			return true;
		} break;
	case EInventoryContainerSlot::LEGGINGS:
		if (Container.Leggings) {
			Container.Leggings = nullptr;
			return true;
		} break;
	case EInventoryContainerSlot::BOOTS:
		if (Container.Boots) {
			Container.Boots = nullptr;
			return true;
		} break;
	default:
		break;
	}
	return false;
}

bool UEquipmentComponent::TryRemove(AItem* Item) {
	if (Item == Container.LeftHand) { return Remove(EInventoryContainerSlot::LEFT_HAND); }
	if (Item == Container.RightHand) { return Remove(EInventoryContainerSlot::RIGHT_HAND); }
	if (Item == Container.Helmet) { return Remove(EInventoryContainerSlot::HELMET); }
	if (Item == Container.Chestplate) { return Remove(EInventoryContainerSlot::CHESTPLATE); }
	if (Item == Container.Leggings) { return Remove(EInventoryContainerSlot::LEGGINGS); }
	if (Item == Container.Boots) { return Remove(EInventoryContainerSlot::BOOTS); }

	return false;
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
				if (ItemsInRange[i].ItemType = EItemType::USEABLE) {
					ItemsInRange[i]->OnUse(Character);
				}
			}
		}
	}
}

//bool UInventoryComponent::PickUp_Validate(AItem* Item) {
//	//If inventory/slot is not full
//	return true;
//}
