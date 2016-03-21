// CC BY-NC 4.0

#include "Framework.h"
#include "Useable.h"

AUseable::AUseable() {

}

//UAnimationAsset* AUseable::GetAnimation() {
//	return NULL
//}

void AUseable::Use_Implementation(ABaseCharacter* Character) {
	return;
}

bool AUseable::Use_Validate(ABaseCharacter* Character) {
	return true;
}