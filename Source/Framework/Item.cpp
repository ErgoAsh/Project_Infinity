// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Item.h"

AItem::AItem(FItemType Data) : ItemData(Data) {
	switch (Data.Type) {
	case 0:  ItemType = EItemType::OTHER; break;
	case 1:  ItemType = EItemType::USEABLE; break;
	case 2:	 ItemType = EItemType::WEAPON; break;
	case 3:  ItemType = EItemType::ARMOR; break;
	case 4:	 ItemType = EItemType::MATERIAL; break;
	case 5:	 ItemType = EItemType::TOOL; break;
	default: ItemType = EItemType::OTHER; break;
	}
	
	// Set this actor to be able to be picked up by actors with InventoryComponent
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	Sphere->InitSphereRadius(100.0f);
	Sphere->SetCollisionProfileName(TEXT("ItemPickUp"));
	RootComponent = Sphere;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComp->SetOnlyOwnerSee(false);
	MeshComp->bCastDynamicShadow = true;
	MeshComp->CastShadow = true;
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->StaticMesh = ItemData.Model.Get();
}
