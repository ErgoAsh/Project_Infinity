// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Consequence.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FExecuteConsequenceEvent);

UENUM()
enum EModifyType {
	Add,
	Remove,
	Multiply,
	Divide,
	AddPercentage,
	RemovePercentage
};

USTRUCT(BlueprintType)
struct FModifier {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Property")
	float AmountModified;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Property")
	TEnumAsByte<EModifyType> Type;
	
	FORCEINLINE bool operator==(const FModifier& Other) {
		return (AmountModified == Other.AmountModified && Type == Other.Type);
	}

	FModifier() {};
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
	virtual bool Execute() = 0;
};