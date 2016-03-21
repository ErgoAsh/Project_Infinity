// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Item.h"

AItem::AItem(FItemType& ItemData) {
	this->ItemData = ItemData;
	switch (ItemData.Type) {
	case 0:  Type = EItemType::OTHER; break;
	case 1:  Type = EItemType::USEABLE; break;
	case 2:	 Type = EItemType::WEAPON; break;
	case 3:  Type = EItemType::ARMOR; break;
	case 4:	 Type = EItemType::MATERIAL; break;
	case 5:	 Type = EItemType::TOOL; break;
	default: Type = EItemType::OTHER; break;
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
	MeshComp->AttachTo(RootComponent);
}
