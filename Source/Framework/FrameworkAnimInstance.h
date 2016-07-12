// CC BY-NC 4.0

#pragma once

#include "Animation/AnimInstance.h"
#include "Action.h"
#include "FrameworkAnimInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FRAMEWORK_API UFrameworkAnimInstance : public UAnimInstance {

	GENERATED_BODY()

public:

	//UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "Animation")
	FOnExecuteEvent ExecuteEvent;

	virtual void NativeInitializeAnimation() override;
	
	
};
