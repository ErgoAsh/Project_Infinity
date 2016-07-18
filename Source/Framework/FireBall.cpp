// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Projectile.h"
#include "Engine.h"
#include "FireBall.h"

UFireBall::UFireBall() {
	SkillName = FString(TEXT("FireBall"));
}

void UFireBall::Execute(ABaseCharacter* Executor) {
	if (Executor->GetWorld() && FireBallMesh != nullptr) {
		AProjectile* FireBall = Executor->GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass());
		//TODO change it to get proper hand and weapon
		FireBall->SetOwner(Executor);
		FireBall->GetMeshComponent()->SetStaticMesh(FireBallMesh.Get());
		FireBall->GetMeshComponent()->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
		FireBall->SetActorLocation(Executor->GetMesh()->GetSocketLocation("WeaponSocketR"));
		FireBall->GetProjectileMovement()->InitialSpeed = 1500;
		FireBall->GetProjectileMovement()->MaxSpeed = 2000;
		FireBall->InitVelocity(Executor->GetActorRotation().Vector() * 2);
	}
	Super::Execute(Executor);
}
