// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Framework.h"
#include "FrameworkGameMode.h"
#include "PlayerCharacter.h"
#include "GameSave.h"

AFrameworkGameMode::AFrameworkGameMode() {
	DefaultPawnClass = APlayerCharacter::StaticClass();
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
