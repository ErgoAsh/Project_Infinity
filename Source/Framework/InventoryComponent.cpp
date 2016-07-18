// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Engine.h"
#include "BaseCharacter.h"
#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent(FEquipment Load) : Equipment(Load) {

	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	Clear();
}

void UInventoryComponent::BeginPlay() {
	ABaseCharacter* Char = Cast<ABaseCharacter>(GetOwner());
	if (Char) {
		if (!RightHandItem) {
			RightHandItem = (AWeapon*)GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass());
			RightHandItem->SetOwner(GetOwner());
			RightHandItem->MeshComp->StaticMesh = StaticMeshLel;
			RightHandItem->bUseDefaultTraceMethod = true;
			RightHandItem->GetRootComponent()->AttachToComponent(Char->GetMesh(),
				FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), TEXT("WeaponSocketR"));
		}
		Equipment.RightHand = RightHandItem;
		RightHandItem->MeshComp->BodyInstance.SetCollisionProfileName("OverlapAll");
		//RightHandItem->MeshComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);

		if (!LeftHandItem) {
			LeftHandItem = (AWeapon*)GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass());
			LeftHandItem->SetOwner(GetOwner());
			LeftHandItem->MeshComp->StaticMesh = StaticMeshLel;
			LeftHandItem->bUseDefaultTraceMethod = true;
			RightHandItem->GetRootComponent()->AttachToComponent(Char->GetMesh(),
				FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), TEXT("WeaponSocketL"));
		}
		Equipment.LeftHand = LeftHandItem;
		LeftHandItem->MeshComp->BodyInstance.SetCollisionProfileName("OverlapAll");
		//LeftHandItem->MeshComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	}
}

void UInventoryComponent::PickUp() {
	for (int32 i = 0; i < ItemsInRange.Num(); i++) {
		if (!ItemsInRange[i]) continue;
		if (!ItemsInRange[i]->IsValidLowLevel()) continue;

		AddItem(ItemsInRange[i]);
		ItemsInRange[i]->MeshComp->DestroyComponent();
	}
}

void UInventoryComponent::Drop(AItem* Item) {
	Delete(Item);

	UStaticMeshComponent* Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Item->MeshComp = Comp;
	Comp->SetOnlyOwnerSee(false);
	Comp->bCastDynamicShadow = true;
	Comp->CastShadow = true;
	Comp->AttachToComponent(Item->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	Comp->StaticMesh = Item->GetItemData().Model.Get();

	FVector Loc = GetOwner()->GetActorLocation();
	Loc.Z -= GetOwner()->GetSimpleCollisionHalfHeight();
	Item->GetRootComponent()->SetWorldLocation(Loc);
}

void UInventoryComponent::OnRegister() {
	Super::OnRegister();
}

AItem* UInventoryComponent::Get(EInventoryContainerSlot ItemSlot) {
	switch (ItemSlot) {
	case EInventoryContainerSlot::LEFT_HAND:
		return Equipment.LeftHand;
	case EInventoryContainerSlot::RIGHT_HAND:
		return Equipment.RightHand;
	case EInventoryContainerSlot::HELMET:
		return Equipment.Helmet;
	case EInventoryContainerSlot::CHESTPLATE:
		return Equipment.Chestplate;
	case EInventoryContainerSlot::LEGGINGS:
		return Equipment.Leggings;
	case EInventoryContainerSlot::BOOTS:
		return Equipment.Boots;
	default:
		return nullptr;
	}
}

bool UInventoryComponent::Set(EInventoryContainerSlot ItemSlot, AItem* Item) {
	if (!Item) {
		return false;
	}
	ABaseCharacter* Char = Cast<ABaseCharacter>(GetOwner());
	if (Char) {
		UInventoryComponent* Inventory = Char->GetInventoryComponent();
		if (Inventory && (Inventory->HasItem(Item) || (Item == LeftHandItem || Item == RightHandItem))) {
			AWeapon* Weapon;
			switch (ItemSlot) {
			case EInventoryContainerSlot::RIGHT_HAND:
				Weapon = Cast<AWeapon>(Item);
				if (Weapon) {
					Equipment.RightHand = Weapon;
					Item->GetRootComponent()->AttachToComponent(Char->GetMesh(),
						FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), TEXT("WeaponSocketR"));
					return true;
				}
				return false;

			case EInventoryContainerSlot::LEFT_HAND:
				Weapon = Cast<AWeapon>(Item);
				if (Weapon) {
					Equipment.LeftHand = Weapon;
					Item->GetRootComponent()->AttachToComponent(Char->GetMesh(),
						FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), TEXT("WeaponSocketL"));
					return false;
				}
				return true;

			case EInventoryContainerSlot::HELMET:
				Equipment.Helmet = Item;
				return true;

			case EInventoryContainerSlot::CHESTPLATE:
				Equipment.Chestplate = Item;
				return true;

			case EInventoryContainerSlot::LEGGINGS:
				Equipment.Leggings = Item;
				return true;

			case EInventoryContainerSlot::BOOTS:
				Equipment.Boots = Item;
				return true;
			default: break;
			}
		}
	}
	return false;
}

bool UInventoryComponent::Remove(EInventoryContainerSlot ItemSlot) {
	switch (ItemSlot) {
	case EInventoryContainerSlot::LEFT_HAND:
		if (Equipment.LeftHand) {
			Equipment.LeftHand = LeftHandItem;
			return true;
		} break;
	case EInventoryContainerSlot::RIGHT_HAND:
		if (Equipment.RightHand) {
			Equipment.RightHand = RightHandItem;
			return true;
		} break;
	case EInventoryContainerSlot::HELMET:
		if (Equipment.Helmet) {
			Equipment.Helmet = NULL;
			return true;
		} break;
	case EInventoryContainerSlot::CHESTPLATE:
		if (Equipment.Chestplate) {
			Equipment.Chestplate = NULL;
			return true;
		} break;
	case EInventoryContainerSlot::LEGGINGS:
		if (Equipment.Leggings) {
			Equipment.Leggings = NULL;
			return true;
		} break;
	case EInventoryContainerSlot::BOOTS:
		if (Equipment.Boots) {
			Equipment.Boots = NULL;
			return true;
		} break;
	default:
		break;
	}
	return false;
}

bool UInventoryComponent::Delete(AItem* Item) {
	if (Item == Equipment.LeftHand) { return Remove(EInventoryContainerSlot::LEFT_HAND); }
	if (Item == Equipment.RightHand) { return Remove(EInventoryContainerSlot::RIGHT_HAND); }
	if (Item == Equipment.Helmet) { return Remove(EInventoryContainerSlot::HELMET); }
	if (Item == Equipment.Chestplate) { return Remove(EInventoryContainerSlot::CHESTPLATE); }
	if (Item == Equipment.Leggings) { return Remove(EInventoryContainerSlot::LEGGINGS); }
	if (Item == Equipment.Boots) { return Remove(EInventoryContainerSlot::BOOTS); }
	InventoryArray.Remove(Item);
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

TArray<AItem*> UInventoryComponent::GetItemsByID(uint8 ID) {
	TArray<AItem*> Items;
	for (int i = 0; i < InventoryArray.Num(); i++) {
		if (InventoryArray[i]->GetItemData().ID == ID) {
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

void UInventoryComponent::AddItem(AItem* Item) {
	Item->SetOwner(GetOwner());
	InventoryArray.Add(Item);
}

bool UInventoryComponent::HasItem(AItem* Item) {
	return InventoryArray.Contains(Item);
}

void UInventoryComponent::InitializeCollision(UShapeComponent* Shape) {
	//Shape->OnComponentBeginOverlap.AddDynamic(this, &UInventoryComponent::OnComponentOverlap);
	//Shape->OnComponentEndOverlap.AddDynamic(this, &UInventoryComponent::OnComponentEndOverlap);
}

void UInventoryComponent::InitializeInput(UInputComponent* Input) {
	Input->BindAction("PickUp", IE_Pressed, this, &UInventoryComponent::PickUp);
}

void UInventoryComponent::OnComponentOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherComp->GetCollisionProfileName().Compare(FName(TEXT("ItemPickUp"))), ESearchCase::IgnoreCase) {
		AItem* VisualItem = Cast<AItem>(OtherActor);
		if (VisualItem) {
			if (!(VisualItem->GetOwner() == GetOwner()) && VisualItem->bPickAble) {
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
