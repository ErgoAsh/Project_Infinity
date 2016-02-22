// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Weapon.h"
#include "BaseCharacter.h"
#include "Item.h"
#include "PhysicsEngine/DestructibleActor.h"
#include "Engine.h"

AWeapon::AWeapon() {
	ItemType = EItemType::WEAPON;
	PrimaryActorTick.bCanEverTick = true;
	bUseDefaultTraceMethod = true;
}

void AWeapon::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) {
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	if (bUseDefaultTraceMethod) {
		ABaseCharacter* Char = Cast<ABaseCharacter>(GetOwner());
		if (Char) {
			if (Char->bIsAttackingLeft || Char->bIsAttackingRight) {
				FVector Start = MeshComp->GetSocketLocation(FName(TEXT("TraceStart")));
				FVector End = MeshComp->GetSocketLocation(FName(TEXT("TraceEnd")));
				FHitResult Result = Trace(Start, End);
				if (Result.GetActor() == this || Result.GetActor() == GetOwner()
					|| Result.GetActor()->GetOwner() == GetOwner()) return;

				ADestructibleActor* Destructible = Cast<ADestructibleActor>(Result.GetActor());
				if (Destructible) {
					if (Destructible->bCanBeDamaged) {
						GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, TEXT("TestB"));
						Destructible->GetDestructibleComponent()->
							ApplyDamage(100, Result.ImpactPoint, (Start - End) * -1, 2500);
					}
				}
				IDamageable* Damageable = Cast<IDamageable>(Result.GetActor());
				if (Damageable) {
					GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, TEXT("Test"));
					Damageable->TakeDamage(GetOwner(), Result);
				}
			}
		}
	}
}

FHitResult AWeapon::Trace(const FVector& StartTrace, const FVector& EndTrace) {
	FCollisionQueryParams Params(FName(TEXT("Hit")), true, Instigator);
	Params.bTraceAsyncScene = true;
	Params.bReturnPhysicalMaterial = true;

	//TArray<AActor*> ActorsToIgnore;
	//ActorsToIgnore.Add(Instigator);
	//ActorsToIgnore.Add(this);

	FCollisionObjectQueryParams ObjectParams(FCollisionObjectQueryParams::InitType::AllObjects);
	FHitResult Result(ForceInit);
	if (GetWorld()->LineTraceSingleByObjectType(Result, StartTrace, EndTrace, ObjectParams, Params)) {
		DrawDebugLine(this->GetWorld(), StartTrace, EndTrace, FColor::Black, true, 1000.f, 10.f);
	}

	return Result;
}

UAnimationAsset* AWeapon::GetAnimation() {
	return Animation;
}
