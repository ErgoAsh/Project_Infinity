// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "EquipmentComponent.h"
#include "BareHand.h"
#include "Engine.h"
#include "BaseCharacter.h"

UEquipmentComponent::UEquipmentComponent(FInventoryContainer Load) {
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sword(TEXT("/Game/ThirdPerson/Meshes/Swords/Medieval_sword.Medieval_sword"));
	StaticMeshLel = Sword.Object;

	Container = Load;
}

void UEquipmentComponent::OnRegister() {
	Super::OnRegister();


	ABaseCharacter* Char = Cast<ABaseCharacter>(GetOwner());
	if (Char) {
		if (!RightHandItem) {
			RightHandItem = (AWeapon*) GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass());
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
			LeftHandItem = (AWeapon*) GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass());
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

void UEquipmentComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	//DrawDebugSphere(
	//	GetWorld(),
	//	LeftHandItem->GetActorLocation(),
	//	LeftHandItem->SphereCollision->GetScaledSphereRadius(),
	//	32,
	//	FColor::Blue
	//);

	//DrawDebugSphere(
	//	GetWorld(),
	//	RightHandItem->GetActorLocation(),
	//	RightHandItem->SphereCollision->GetScaledSphereRadius(),
	//	32,
	//	FColor::Blue
	//);
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
	if (Item->ItemType != EItemType::USEABLE) {
		ABaseCharacter* Char = Cast<ABaseCharacter>(GetOwner());
		UInventoryComponent* Inventory = (Char) ? Char->GetInventoryComponent() : NULL;
		if (Inventory && (Inventory->HasItem(Item) || (Item == LeftHandItem || Item == RightHandItem))) {
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
	//Maybe change it to:
	//if (Item 'instanceof' Weapon) {
	//	switch (Item.SlotType)

	if (Item == Container.LeftHand) { return Remove(EInventoryContainerSlot::LEFT_HAND); }
	if (Item == Container.RightHand) { return Remove(EInventoryContainerSlot::RIGHT_HAND); }
	if (Item == Container.Helmet) { return Remove(EInventoryContainerSlot::HELMET); }
	if (Item == Container.Chestplate) { return Remove(EInventoryContainerSlot::CHESTPLATE); }
	if (Item == Container.Leggings) { return Remove(EInventoryContainerSlot::LEGGINGS); }
	if (Item == Container.Boots) { return Remove(EInventoryContainerSlot::BOOTS); }

	return false;
}

