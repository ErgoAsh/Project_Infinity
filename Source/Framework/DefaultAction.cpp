// CC BY-NC 4.0

#include "Framework.h"
#include "DefaultAction.h"
#include "Engine.h"
#include "Singleton.h"
#include "Action.h"

UDefaultAction::UDefaultAction() {
	ChangeEvent = NewObject<UEventContainer>();
}

UAnimationAsset* UDefaultAction::GetAnimation() {
	return nullptr;
}

void UDefaultAction::Execute(ABaseCharacter* Executor){
	ChangeEvent->Event.Broadcast(Executor, this);
}

UEventContainer* UDefaultAction::GetExecuteEvent() {
	return ChangeEvent;
}