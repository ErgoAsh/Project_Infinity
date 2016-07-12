// CC BY-NC 4.0

#include "Framework.h"
#include "Effect.h"

UEffect::UEffect() {}

bool UEffect::Execute_Implementation() {
	return false;
}

EEffectType UEffect::GetEffectType() {
	unimplemented();
	return EEffectType::VISUAL; //TODO make undefined?
}
