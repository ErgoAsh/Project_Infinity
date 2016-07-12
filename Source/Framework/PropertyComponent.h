// CC BY-NC 4.0

#pragma once

#include "Components/ActorComponent.h"
#include "Effect.h"
#include "PropertyComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRAMEWORK_API UPropertyComponent : public UActorComponent {

	GENERATED_BODY() //TODO delete or redone this file

	UPROPERTY(VisibleAnywhere, Category = "Property")
	int32 Health;
	UPROPERTY(VisibleAnywhere, Category = "Property")
	int32 MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	int32 Mana;
	UPROPERTY(VisibleAnywhere, Category = "Property")
	int32 MaxMana;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	int32 Stamina;
	UPROPERTY(VisibleAnywhere, Category = "Property")
	int32 MaxStamina;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	int32 Money;
	UPROPERTY(VisibleAnywhere, Category = "Property")
	int32 MaxMoney;

	//UPROPERTY(VisibleAnywhere, Category = "Property")
	//TArray<UEffect*> Effects;

public:	
	// Sets default values for this component's properties
	UPropertyComponent();

	// Called when the game starts
	// TODO add save/load system
	virtual void BeginPlay() override;

	int32 GetMana() const { return Mana; }
	int32 GetMaxMana() const { return MaxMana; }

	int32 GetStamina() const { return Stamina; }
	int32 GetMaxStamina() const { return MaxStamina; }

	int32 GetHealth() const { return Health; }
	int32 GetMaxHealth() const { return MaxHealth; }

	int32 GetMoney() const { return Money; }
	int32 GetMaxMoney() const { return MaxMoney; }

	//TArray<UEffect*> GetEffects() const { return Effects; }
	
};
