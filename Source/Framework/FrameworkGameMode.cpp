// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Framework.h"
#include "FrameworkGameMode.h"
#include "PlayerCharacter.h"

AFrameworkGameMode::AFrameworkGameMode() {
	//DefaultPawnClass = APlayerCharacter::StaticClass();
}

void AFrameworkGameMode::PostLogin(APlayerController* NewPlayer) {
	//UVaRestRequestJSON::ConstructRequestExt();
}

//bool AFrameworkGameMode::SavePlayer(ABaseCharacter* Player) {
//	UGameSave* Save = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
//
//	Save->PlayerName = Player->GetHumanReadableName();
//	Save->Health = Player->Health;
//	Save->Mana = 0;
//	
//	UGameplayStatics::SaveGameToSlot(Save, Save->SlotName, Save->UserIndex);
//}
