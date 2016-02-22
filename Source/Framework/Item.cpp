// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Item.h"

AItem::AItem(EItemID ID, EItemType Type) {
	ItemID = ID;
	ItemType = Type;

	// Set this actor to be able to be picked up by actors with InventoryComponent
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	Sphere->InitSphereRadius(100.0f);
	Sphere->SetCollisionProfileName(TEXT("ItemPickUp"));
	RootComponent = Sphere;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComp->SetOnlyOwnerSee(false);            // all players will see this meshs
	MeshComp->bCastDynamicShadow = true;
	MeshComp->CastShadow = true;
	MeshComp->AttachTo(RootComponent);

	DisplayName = TEXT("Bare Hands");
}
