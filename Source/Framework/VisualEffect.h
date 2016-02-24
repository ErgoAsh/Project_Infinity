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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Visual")
	TAssetPtr<UParticleEmitter> Particle;

	UVisualEffect();
	//TODO let's try to add them without by making it Actor
	//void BeginPlay() override;
	//void Tick() override;
	
};
