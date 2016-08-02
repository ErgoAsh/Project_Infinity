// CC BY-NC 4.0

#include "Framework.h"
#include "Catalyst.h"
#include "ActiveSkill.h"
#include "Engine/EngineBaseTypes.h"

bool ACatalyst::ExecuteSpell(ABaseCharacter* Character, UActiveSkill* Spell) {
	if (Spell->CheckRequirements(Character)) {
		Spell->Execute(Character);
		return true;
	}
	return false;
}

// void ACatalyst::UseMain(class ABaseCharacter* BaseCharacter) {
// 	//Make able to execute spell
// }
// 
// void ACatalyst::UseSecond(class ABaseCharacter* BaseCharacter) {
// 	//Attack
// }

void ACatalyst::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	//Handle attack?
}
