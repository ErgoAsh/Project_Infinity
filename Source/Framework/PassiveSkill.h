// CC BY-NC 4.0

#pragma once

#include "Skill.h"
#include "PassiveSkill.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class FRAMEWORK_API UPassiveSkill : public USkill {

	GENERATED_BODY()
	
public:
	//TODO make 
	UFUNCTION(BlueprintImplementableEvent, Category = "Skill") //Native/Callable?
	void Apply(ABaseCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void UnApply(ABaseCharacter* Character);
};
