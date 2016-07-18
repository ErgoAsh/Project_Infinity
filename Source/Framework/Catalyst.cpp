// CC BY-NC 4.0

#include "Framework.h"
#include "Catalyst.h"
#include "ActiveSkill.h"

bool ACatalyst::ExecuteSpell(ABaseCharacter* Character, UActiveSkill* Spell) {
	if (Spell->CheckRequirements(Character)) {
		Spell->Execute(Character);
		return true;
	}
	return false;
}
