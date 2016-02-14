// CC BY-NC 4.0

#include "Framework.h"
#include "EventContainter.h"

UEventContainer::UEventContainer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
}

TArray<TMulticastScriptDelegate*> IEventContainer::GetEvents() {
	unimplemented();
	return TArray();
}


