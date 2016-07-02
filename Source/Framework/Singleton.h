// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Engine/DataTable.h"
#include "Singleton.generated.h"

/**
 * 
 */
UCLASS()
class FRAMEWORK_API USingleton : public UObject {

	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Game")
	UDataTable* ItemData;
	
	UPROPERTY(VisibleAnywhere, Category = "Game")
	UDataTable* EffectData;
	
};
