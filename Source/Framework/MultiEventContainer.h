// CC BY-NC 4.0

#pragma once

#include "Framework.h"
#include "Delegates\IDelegateInstance.h"
#include "UObject\ScriptDelegates.h"
#include "DelegateBase.h"
#include "..\..\..\4.10\Engine\Source\Runtime\Core\Public\Delegates\DelegateSignatureImpl_Variadics.inl"
#include "MultiEventContainer.generated.h"

/**
*
*/
UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UMultiEventContainer : public UInterface {

	GENERATED_UINTERFACE_BODY()

};

class FRAMEWORK_API IMultiEventContainer {

	GENERATED_IINTERFACE_BODY()

public:
	//UFUNCTION(BlueprintCallable, Category = "Event")
	//virtual TArray<FDelegate> GetEvents() = 0;

};
