// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "BaseCharacter.h"
#include "FrameworkGameMode.generated.h"

UCLASS(minimalapi)
class AFrameworkGameMode : public AGameMode {

	GENERATED_BODY()

public:
	AFrameworkGameMode();

	//bool SavePlayer(ABaseCharacter* Player);
	//UBaseCharacter LoadPlayer()
};



