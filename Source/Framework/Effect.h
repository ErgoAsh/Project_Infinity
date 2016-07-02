// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Consequence.h"
#include "Effect.generated.h"

UENUM()
enum EEffectType {
	BUFF,
	DEBUFF,
	VISUAL
	//Anything else?
};

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UEffect : public UConsequence {

	GENERATED_UINTERFACE_BODY()

};


class FRAMEWORK_API IEffect {

	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual bool Execute() = 0;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual EEffectType GetEffectType() = 0;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual float GetDuration() = 0;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual TArray<FModifier> GetModifiers() = 0;

	//TODO add some theards to make the duration dissapear or something
};
