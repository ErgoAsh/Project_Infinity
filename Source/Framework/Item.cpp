// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Item.h"

AItem::AItem() {
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	Sphere->InitSphereRadius(100.0f);
	Sphere->SetCollisionProfileName(TEXT("ItemPickUp"));
	RootComponent = Sphere;


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComp->SetOnlyOwnerSee(false);
	MeshComp->bCastDynamicShadow = true;
	MeshComp->CastShadow = true;
	MeshComp->SetupAttachment(RootComponent);
	if (MeshComp->StaticMesh != nullptr) {
		MeshComp->StaticMesh = GetItemData()->Model.Get(); //TODO load
	}
}

FItemData* AItem::GetItemData() {
	bool bIsValid;
	USingleton* Singleton = UFrameworkLibrary::GetSignleton(bIsValid);
	if (bIsValid) {
		return Singleton->ItemData->FindRow<FItemData>(FName(*FString::FromInt(ID)), FString("GENERAL"));
	} else {
		UE_LOG(Debugg, Warning, TEXT("AItem::GetItemData(): Singleton is NULL"));
		return nullptr;
	}
}
