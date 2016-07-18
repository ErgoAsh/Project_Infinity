// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Consequence.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FExecuteConsequenceEvent);

UENUM(BlueprintType)
enum class EModifyType : uint8 {
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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Properties")
	float AmountModified;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Properties")
	TEnumAsByte<EModifyType> Type;

	FModifier() {};
};

FORCEINLINE bool operator==(const FModifier& A, const FModifier& B) {
	return (A.AmountModified == B.AmountModified && A.Type == B.Type);
}

/**
*
*/
UINTERFACE(Blueprintable)
class UConsequence : public UInterface {

	GENERATED_UINTERFACE_BODY()

};

class FRAMEWORK_API IConsequence {

	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Effect")
	bool Execute(); //What exactly it should do...
	//More arguments?

	//Should add GetModifiers (or just in Effect)? Seems logic...
};