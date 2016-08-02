// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Engine.h"
#include "BaseCharacter.h"
#include "InventoryComponent.h"
#include "Pickable.h"

UInventoryComponent::UInventoryComponent(FEquipment Load) : Equipment(Load) {

	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	Clear();
}

void UInventoryComponent::BeginPlay() {
	ABaseCharacter* Char = Cast<ABaseCharacter>(GetOwner());
}

void UInventoryComponent::PickUp() {
	for (int32 i = 0; i < ItemsInRange.Num(); i++) {
		if (!ItemsInRange[i]) continue;
		if (!ItemsInRange[i]->IsValidLowLevel()) continue;

		if (!ItemsInRange[i]->IsCollectable()) continue;
		APickable* Pickable = Cast<APickable>(ItemsInRange[i]);
		if (Pickable != nullptr) {
			Pickable->PickUp();
			ItemsInRange[i]->Destroy();
		} else {
			AddItem(ItemsInRange[i]);
			ItemsInRange[i]->DestroyMesh();
		}
	}
}

void UInventoryComponent::Drop(AItem* Item) {
	TryRemove(Item);

	UStaticMeshComponent* Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Comp->StaticMesh = Item->GetItemData()->Model.Get();
	Comp->SetOnlyOwnerSee(false);
	Comp->bCastDynamicShadow = true;
	Comp->CastShadow = true;
	Item->SetMeshComponent(Comp);
	Comp->AttachToComponent(Item->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));

	FVector Loc = GetOwner()->GetActorLocation();
	Loc.Z -= GetOwner()->GetSimpleCollisionHalfHeight();
	Item->GetRootComponent()->SetWorldLocation(Loc);
}

void UInventoryComponent::OnRegister() {
	Super::OnRegister();
}

AItem* UInventoryComponent::Get(uint8 Slot) {
	switch (Slot) {
	case 1: return Equipment.Helmet;
	case 2: return Equipment.Chestplate;
	case 3: return Equipment.Leggings;
	case 4: return Equipment.Boots;
	case 5: return Equipment.LeftHand;
	case 6: return Equipment.RightHand;
	default: return nullptr;
	}
}

uint8 UInventoryComponent::GetSlot(AItem* Item) {
	if (Item == Equipment.Helmet) return 1;
	else if (Item == Equipment.Chestplate) return 2;
	else if (Item == Equipment.Leggings) return 3;
	else if (Item == Equipment.Boots) return 4;
	else if (Item == Equipment.LeftHand) return 5;
	else if (Item == Equipment.RightHand) return 6;
	else return 0;
}

bool UInventoryComponent::Set(uint8 Slot, AItem* Item) {
	if (Item == nullptr) {
		return false;
	}
	ABaseCharacter* Char = Cast<ABaseCharacter>(GetOwner());
	if (Char == nullptr) {
		return false;
	}
	AWeapon* Weapon;
	switch (Slot) {
	case 1:
		Equipment.Helmet = Item;
		return true;

	case 2:
		Equipment.Chestplate = Item;
		return true;

	case 3:
		Equipment.Leggings = Item;
		return true;

	case 4:
		Equipment.Boots = Item;
		return true;

	case 5:
		Weapon = Cast<AWeapon>(Item);
		if (Weapon) {
			Equipment.LeftHand = Weapon;
			Item->GetRootComponent()->AttachToComponent(Char->GetMesh(),
				FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), TEXT("WeaponSocketL")); //TODO get from Singleton
			return false;
		}
		return true;

	case 6:
		Weapon = Cast<AWeapon>(Item);
		if (Weapon) {
			Equipment.RightHand = Weapon;
			Item->GetRootComponent()->AttachToComponent(Char->GetMesh(),
				FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), TEXT("WeaponSocketR")); //TODO get from Singleton
			return true;
		}
		return false;

	default: return false;
	}
}

bool UInventoryComponent::Remove(uint8 Slot) {
	switch (Slot) {
	case 1:
		if (Equipment.Helmet) {
			Equipment.Helmet = nullptr;
			return true;
		} break;
	case 2:
		if (Equipment.Chestplate) {
			Equipment.Chestplate = nullptr;
			return true;
		} break;
	case 3:
		if (Equipment.Leggings) {
			Equipment.Leggings = nullptr;
			return true;
		} break;
	case 4:
		if (Equipment.Boots) {
			Equipment.Boots = nullptr;
			return true;
		} break;
	case 5:
		if (Equipment.LeftHand) {
			Equipment.LeftHand = nullptr;
			return true;
		} break;
	case 6:
		if (Equipment.RightHand) {
			Equipment.RightHand = nullptr;
			return true;
		} break;
	default:
		break;
	}
	return false;
}

bool UInventoryComponent::TryRemove(AItem* Item) {
	if (Item == Equipment.Helmet) { return Remove(1); }
	if (Item == Equipment.Chestplate) { return Remove(2); }
	if (Item == Equipment.Leggings) { return Remove(3); }
	if (Item == Equipment.Boots) { return Remove(4); }
	if (Item == Equipment.LeftHand) { return Remove(5); }
	if (Item == Equipment.RightHand) { return Remove(6); }
	InventoryArray.Remove(Item);
	return false;
}

TArray<AItem*> UInventoryComponent::GetItemsByType(EItemType ItemType) {
	TArray<AItem*> Items;
	for (int i = 0; i < InventoryArray.Num(); i++) {
		if (InventoryArray[i]->GetItemData()->Type == ItemType) {
			Items.Add(InventoryArray[i]);
		}
	}
	return Items;
}

TArray<AItem*> UInventoryComponent::GetItemsByID(uint8 ID) {
	TArray<AItem*> Items;
	for (int i = 0; i < InventoryArray.Num(); i++) {
		if (InventoryArray[i]->GetItemData()->ID == ID) {
			Items.Add(InventoryArray[i]);
		}
	}
	return Items;
}

AItem* UInventoryComponent::GetItem(uint8 Index) {
	return InventoryArray[Index];
}

void UInventoryComponent::Clear() {
	for (AItem* Item : InventoryArray) {
		Item->Destroy();
		InventoryArray.Remove(Item);
	}
	InventoryArray.Empty();
}

void UInventoryComponent::RemoveFromArray(uint8 Index) {
	InventoryArray.RemoveAt(Index);
}

void UInventoryComponent::AddItem(AItem* Item) {
	if (Item == nullptr) return;
	FItemData* Data = Item->GetItemData();
	if (Data != nullptr && Data->bCanStack) {
		uint8 AddedAmount = Item->GetAmount();
		uint8 FullAmount = 0;
		for (AItem* CurrentItem : GetItemsByID(Item->GetID())) {
			if (CurrentItem == nullptr) {
				TryRemove(CurrentItem);
				continue;
			}
			//TODO
			//CurrentItem->GetAmount() += Amount;
			//if (Data->MaxAmountPerStack > CurrentItem->GetAmount()) {
			//	Amount -= CurrentItem->GetAmount() - Data->MaxAmountPerStack;
			//	//CurrentItem->GetAmount() == Data->MaxAmountPerStack;
			//}

			//FullAmount += 

			//if 
			break; //Currently there can be only 1 stacked item (unless I add such feature)
		}
	} else {
		InventoryArray.Add(Item);
		//TODO delete item obj;
	}
	Item->SetOwner(GetOwner());
}

bool UInventoryComponent::HasItem(AItem* Item) {
	return InventoryArray.Contains(Item);
}

void UInventoryComponent::InitializeCollision(UShapeComponent* Shape) {
	Shape->OnComponentBeginOverlap.AddDynamic(this, &UInventoryComponent::OnComponentOverlap);
	Shape->OnComponentEndOverlap.AddDynamic(this, &UInventoryComponent::OnComponentEndOverlap);
}

void UInventoryComponent::InitializeInput(UInputComponent* Input) {
	Input->BindAction("PickUp", IE_Pressed, this, &UInventoryComponent::PickUp);
}

void UInventoryComponent::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherComp->GetCollisionProfileName().Compare(FName(TEXT("ItemPickUp"))), ESearchCase::IgnoreCase) {
		AItem* VisualItem = Cast<AItem>(OtherActor);
		if (VisualItem != nullptr && VisualItem->GetOwner() != GetOwner()) {
			APickable* Pickable = Cast<APickable>(VisualItem);
			if (Pickable != nullptr && Pickable->bPickupOnOverlap) {
				Pickable->PickUp();
				Pickable->Destroy();
			} else {
				ItemsInRange.Add(VisualItem);
				bHasItemsInRange = true;
			}
		}
	}
}

void UInventoryComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherComp->GetCollisionProfileName().Compare(FName(TEXT("ItemPickUp"))), ESearchCase::IgnoreCase) {
		AItem* VisualItem = Cast<AItem>(OtherActor);
		if (VisualItem) {
			ItemsInRange.Remove(VisualItem);
			bHasItemsInRange = false;
		}
	}
}
