// CC BY-NC 4.0

#pragma once

#include "Components/ActorComponent.h"
#include "DefenseComponent.generated.h"

UCLASS(ClassGroup = "Character", meta = (BlueprintSpawnableComponent))
class FRAMEWORK_API UDefenseComponent : public UActorComponent {

	GENERATED_BODY()

public:	
	UDefenseComponent();

	//////////////////////////////////////////////////////////////////////////
	// Physical defenses

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense")
	UFrameworkAttribute* Slash;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense")
	UFrameworkAttribute* Pierce;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense")
	UFrameworkAttribute* Blunt;

	//////////////////////////////////////////////////////////////////////////
	// Environmental defense

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense")
	UFrameworkAttribute* Magic;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense")
	UFrameworkAttribute* Lightning;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense")
	UFrameworkAttribute* Fire;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense")
	UFrameworkAttribute* Ice;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense")
	UFrameworkAttribute* Dark;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense")
	UFrameworkAttribute* Mind;

	//////////////////////////////////////////////////////////////////////////
	// Other
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense")
	UFrameworkAttribute* Poise;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense")
	UFrameworkAttribute* Speed;

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void ClearModifiers();		
};
