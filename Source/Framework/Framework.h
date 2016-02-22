// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Debugg, Log, All);

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text)

#endif
