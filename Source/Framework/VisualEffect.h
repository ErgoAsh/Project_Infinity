// CC BY-NC 4.0

#pragma once

#include "Effect.h"
#include "VisualEffect.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FRAMEWORK_API UVisualEffect : public UEffect {

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Visual")
	FVector Location;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Visual")
	TAssetPtr<UParticleEmitter> Particle;

	UVisualEffect();
	void BeginPlay() override;
	void Tick() override;
	
};
