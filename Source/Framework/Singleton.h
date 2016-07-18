// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Engine/DataTable.h"
#include "Singleton.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FRAMEWORK_API USingleton : public UObject {

	GENERATED_BODY()
	
public:
	USingleton();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game")
	UDataTable* ItemData;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game")
	UDataTable* EffectData;
	
};
