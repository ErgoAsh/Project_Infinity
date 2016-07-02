// CC BY-NC 4.0

#include "Framework.h"
#include "DefaultAction.h"
#include "Engine.h"
#include "Singleton.h"
#include "Action.h"

UDefaultAction::UDefaultAction() {
}

UAnimationAsset* UDefaultAction::GetAnimation() {
	USingleton* Singleton = Cast<USingleton>(GEngine->GameSingleton);
	//return Singleton->DefaultAnimation;
	return NULL;
}

void UDefaultAction::Execute(ABaseCharacter* Executor){
	ChangeEvent.Event.Broadcast(Executor);
}

FEventContainer& UDefaultAction::GetEvent() {
	return ChangeEvent;
}