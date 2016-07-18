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
	static USingleton* GetSignleton(bool& IsValid);
	
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create Object from Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint"), Category = Game)
	static UObject* CreateObject(UObject* WorldContextObject, UClass* BaseClass);
};
