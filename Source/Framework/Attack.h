// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Attack.generated.h"

/**
 * 
 */
UCLASS()
class FRAMEWORK_API UAttack : public UObject {

	GENERATED_BODY()
	
	UAnimSequence* Animation;
	FExecuteEvent ExecuteEvent;

public:
	UDodge();

	UFUNCTION(BlueprintCallable, Category = "Skill")
	UAnimationAsset* GetAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	void Execute(ABaseCharacter* Executor) override;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	TArray<TMulticastScriptDelegate*> GetEvents() override;

};
