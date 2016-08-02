// CC BY-NC 4.0

#pragma once

#include "Item.h"
#include "Pickable.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FRAMEWORK_API APickable : public AItem {

	GENERATED_BODY()
	
public:
	APickable() : AItem() {};

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	bool bPickupOnOverlap;

	UFUNCTION(BlueprintImplementableEvent, Category = "Item")
	void PickUp();
};
