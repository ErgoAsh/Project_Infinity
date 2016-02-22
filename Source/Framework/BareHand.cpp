// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "BareHand.h"
#include "Engine.h"

ABareHand::ABareHand() {
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereCollision->SetSphereRadius(35.0f);
	SphereCollision->AttachTo(RootComponent);
	bUseDefaultTraceMethod = false;
}

void ABareHand::DamageActors() {
	TArray<FOverlapInfo> Info = SphereCollision->GetOverlapInfos();
	for (int32 i = 0; i < SphereCollision->GetOverlapInfos().Num(); i++) {
		FHitResult Result = Info[i].OverlapInfo;
		if (Result.GetActor() == this || Result.GetActor() == GetOwner()
			|| Result.GetActor()->GetOwner() == GetOwner()) continue;
		ADestructibleActor* Destructible = Cast<ADestructibleActor>(Result.GetActor());
		if (Destructible) {
			FVector Self = GetTransform().GetTranslation();
			FVector Other = Result.GetActor()->GetTransform().GetTranslation();
			if (Destructible->bCanBeDamaged) {
				//if (Destructible->GetDestructibleComponent()->)
				Destructible->GetDestructibleComponent()->
					ApplyDamage(100, GetActorLocation(), (Result.ImpactPoint - GetActorLocation()) * -1, 2500);
			}
		}
	}
}
