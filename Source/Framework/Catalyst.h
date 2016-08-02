// CC BY-NC 4.0

#pragma once

#include "Item.h"
#include "ActiveSkill.h"
#include "Catalyst.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FRAMEWORK_API ACatalyst : public AWeapon {

	GENERATED_BODY()
	
	//TODO array of spells supported by catalyst?
	
public:
	UFUNCTION(BlueprintCallable, Category = "Item")
	bool ExecuteSpell(ABaseCharacter* Character, UActiveSkill* Spell);
// 
// 	UFUNCTION(BlueprintCallable, Category = "Item")
// 	virtual void UseMain(class ABaseCharacter* BaseCharacter) override;
// 
// 	UFUNCTION(BlueprintCallable, Category = "Item")
// 	virtual void UseSecond(class ABaseCharacter* BaseCharacter) override;

	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;


};
