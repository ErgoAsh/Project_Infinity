// CC BY-NC 4.0

#pragma once

#include "Item.h"
#include "ActiveSkill.h"
#include "Catalyst.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FRAMEWORK_API ACatalyst : public AItem {

	GENERATED_BODY()
	
	//TODO array of spells supported by catalyst?
	
public:
	UFUNCTION(BlueprintCallable, Category = "Item")
	bool ExecuteSpell(ABaseCharacter* Character, UActiveSkill* Spell);
	
};
