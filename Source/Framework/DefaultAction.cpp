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
	USingleton* Singleton = Cast<USingleton>(GEngine->GameSingleton);
	//return Singleton->DefaultAnimation;
	return NULL;
}

void UDefaultAction::Execute(ABaseCharacter* Executor){
	ChangeEvent->ToEvent().Broadcast(Executor);
}

// FExecuteEvent& UDefaultAction::OnExecute() {
// 	return Execute;
// }

UEventContainer* UDefaultAction::GetExecuteEvent() {
	return ChangeEvent;
}