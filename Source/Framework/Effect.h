// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Consequence.h"
#include "Effect.generated.h"

/**
 * 
 */
UCLASS()
class FRAMEWORK_API UEffect : public UObject, public IConsequence {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	FVector Location;

	UPROPERTY()
	uint8 Range;

	UPROPERTY()
	uint8 Duration;

	//TArray<UModifier> Modifiers;

public:
	UEffect();

	UFUNCTION(BlueprintCallable, Category = "Effect")
	bool Execute() override;
};
