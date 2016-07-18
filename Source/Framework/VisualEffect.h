// CC BY-NC 4.0

#pragma once

#include "Effect.h"
#include "VisualEffect.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FRAMEWORK_API UVisualEffect : public UEffect { //ParticleSpawner with TArray<UEffect> variable instead?

	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere, Category = "Visual")
	TAssetPtr<UParticleEmitter> Particle;

	//UPROPERTY(VisibleAnywhere, Category = "Visual")
	FVector Location; //Actor/Pawn instead or maybe add location AND actor/pawn with bool to check

	//UPROPERTY(VisibleAnywhere, Category = "Visual")
	uint8 Range; //Delete I think, this should be in AreaEffect or something similar

	//UPROPERTY(VisibleAnywhere, Category = "Visual")
	bool bIsExecuted;

public:
	UVisualEffect();
	UVisualEffect(TAssetPtr<UParticleEmitter> Particle);

	bool Execute_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual EEffectType GetEffectType() override;
};
