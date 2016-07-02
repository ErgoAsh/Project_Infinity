// CC BY-NC 4.0

#pragma once

#include "Effect.h"
#include "VisualEffect.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FRAMEWORK_API UVisualEffect : public UClass, public IEffect {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	TAssetPtr<UParticleEmitter> Particle;

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	TArray<FModifier> Modifiers;

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	FVector Location; //Actor/Pawn instead or maybe add location AND actor/pawn with bool to check

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	uint8 Range; //Delete I think, this should be in AreaEffect or something similar

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	float Duration;

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	bool IsExecuted;

public:
	UVisualEffect();
	UVisualEffect(TAssetPtr<UParticleEmitter> Particle);

	//They may not work
	//Change them later to Func_Implementation() style

	UFUNCTION(BlueprintCallable, Category = "Effect")
	bool Execute() override;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	EEffectType GetEffectType() override;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	float GetDuration() override;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	TArray<FModifier> GetModifiers() override;
};
