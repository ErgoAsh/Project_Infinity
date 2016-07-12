// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Consequence.h"
#include "Effect.generated.h"

UENUM(BlueprintType)
enum class EEffectType : uint8 {
	BUFF   UMETA(DisplayName = "Buff"),
	DEBUFF UMETA(DisplayName = "Debuff"),
	VISUAL UMETA(DisplayName = "Visual")
};

UCLASS(Abstract, Blueprintable, BlueprintType)
class FRAMEWORK_API UEffect : public UObject, public IConsequence {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Effect")
	float Duration;

	//UPROPERTY(VisibleAnywhere, Category = "Effect")
	TArray<FModifier> Modifiers;

public:
	UEffect();

	virtual bool Execute_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual EEffectType GetEffectType(); //Why =0 doesn't work?

	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual float GetDuration() { return Duration; }

	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual TArray<FModifier> GetModifiers() { return Modifiers; }

	//TODO add some theards to make the duration dissapear or something
};
