// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework.h"
#include "Projectile.h"
#include "Engine.h"
#include "FireBall.h"

UFireBall::UFireBall() {
	SkillName = FName(TEXT("FireBall"));

	//TODO delete and get from somewhere else
	static ConstructorHelpers::FObjectFinder<UAnimSequence> Animation(TEXT(
		"AnimSequence'/Game/Mannequin/Animations/ThirdPersonJump_Start.ThirdPersonJump_Start'"));
	if (Animation.Succeeded()) {
		Property = Animation.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Ball(TEXT(
		"StaticMesh'/Game/Geometry/Meshes/SM_Rock.SM_Rock'"));
	if (Ball.Succeeded()) {
		FireBallMesh = Ball.Object;
	}
}

UAnimationAsset* UFireBall::GetAnimation() {
	return (UAnimationAsset*) Property;
}

void UFireBall::Execute(ABaseCharacter* Executor) {
	if (Executor->GetWorld()) {
		AProjectile* FireBall = Executor->GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass());
		//TODO change it to get proper hand and weapon
		FireBall->SetOwner(Executor);
		FireBall->GetMeshComponent()->SetStaticMesh(FireBallMesh);
		FireBall->GetMeshComponent()->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
		FireBall->SetActorLocation(Executor->GetMesh()->GetSocketLocation("WeaponSocketR"));
		FireBall->GetProjectileMovement()->InitialSpeed = 1500;
		FireBall->GetProjectileMovement()->MaxSpeed = 2000;
		FireBall->InitVelocity(Executor->GetActorRotation().Vector() * 2);
	}
	Super::Execute(Executor);
}
