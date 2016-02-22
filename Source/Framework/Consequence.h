// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Consequence.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FExecuteConsequenceEvent);

UENUM()
enum ModifyType {
	Add,
	Remove,
	Multiply,
	Divide,
	AddPercentage,
	RemovePercentage
};

USTRUCT()
struct FModifier {
	float AmountModified;
	ModifyType Type;

	FModifier(ModifyType Type) {
		this->Type = Type;
	};

	//Should be added?
	//virtual bool Modify() = 0;
};

/**
*
*/
UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UConsequence : public UInterface {

	GENERATED_UINTERFACE_BODY()

};

class FRAMEWORK_API IConsequence {

	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Effect")
	bool Execute();
};