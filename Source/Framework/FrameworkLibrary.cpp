// CC BY-NC 4.0

#include "Framework.h"
#include "Engine.h"
#include "FrameworkLibrary.h"

UFrameworkLibrary::UFrameworkLibrary() {
}

USingleton* UFrameworkLibrary::GetSignleton(bool& IsValid) {
	IsValid = false;
	USingleton* DataInstance = Cast<USingleton>(GEngine->GameSingleton);

	if (!DataInstance) return NULL;
	if (!DataInstance->IsValidLowLevel()) return NULL;

	IsValid = true;
	return DataInstance;
}
