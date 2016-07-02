// CC BY-NC 4.0

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Singleton.h"
#include "FrameworkLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FRAMEWORK_API UFrameworkLibrary : public UBlueprintFunctionLibrary {

	GENERATED_BODY()

public:
	UFrameworkLibrary();

	UFUNCTION(BlueprintPure, Category = "Framework")
	USingleton* GetSignleton(bool& IsValid);
	
};
