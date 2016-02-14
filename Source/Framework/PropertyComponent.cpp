// CC BY-NC 4.0

#include "Framework.h"
#include "PropertyComponent.h"


// Sets default values for this component's properties
UPropertyComponent::UPropertyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;

	// ...
}


// Called when the game starts
void UPropertyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

