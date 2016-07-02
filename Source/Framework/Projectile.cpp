// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Framework.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
//#include "Damageable.h"
#include "PhysicsEngine/DestructibleActor.h"
#include "Components/DestructibleComponent.h"

AProjectile::AProjectile() {
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	//CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
		// set up a notification for when this component hits something blocking

		// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AProjectile::InitVelocity(const FVector& ShootDirection) {
	if (ProjectileMovement) {
		// set the projectile's velocity to the desired direction
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
	}
}

void AProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherActor != GetOwner()) 
			&& (OtherActor->GetOwner() != GetOwner()) && (OtherComp != NULL)) {
		//IDamageable* Damageable = Cast<IDamageable>(OtherActor);
		//if (Damageable) {
		//	Damageable->TakeDamage(this, Hit);
		//}
		ADestructibleActor* Destructible = Cast<ADestructibleActor>(OtherActor);
		if (Destructible) {
			if (Destructible->bCanBeDamaged) {
				Destructible->GetDestructibleComponent()->
					ApplyDamage(100, GetActorLocation(), (Hit.ImpactPoint - GetActorLocation()) * -1, 2500);
			}
		}
		if (OtherComp->IsSimulatingPhysics()) {
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}
		Destroy();
	}
}