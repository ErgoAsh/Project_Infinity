// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Effect.generated.h"

/**
 * 
 */
UCLASS()
class FRAMEWORK_API UEffect : public UObject {

	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Visual")
	TAssetPtr<UParticleEmitter> Particle;
	
};
