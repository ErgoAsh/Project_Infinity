// CC BY-NC 4.0

#pragma once

#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "FrameworkGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FRAMEWORK_API UFrameworkGameInstance : public UGameInstance {

	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Engine")
	FStreamableManager AssetLoader;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Engine")
	FStreamableManager& GetStreamableManager() { return AssetLoader; }
	
};
