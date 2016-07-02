// CC BY-NC 4.0

#pragma once

#include "Components/ActorComponent.h"
#include "Effect.h"
#include "PropertyComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRAMEWORK_API UPropertyComponent : public UActorComponent {

	GENERATED_BODY() //TODO delete or redone this file

	UPROPERTY(VisibleAnywhere, Category = "Property")
	uint16 Health;
	UPROPERTY(VisibleAnywhere, Category = "Property")
	uint16 MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	uint16 Mana;
	UPROPERTY(VisibleAnywhere, Category = "Property")
	uint16 MaxMana;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	uint16 Stamina;
	UPROPERTY(VisibleAnywhere, Category = "Property")
	uint16 MaxStamina;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	uint16 Money;
	UPROPERTY(VisibleAnywhere, Category = "Property")
	uint16 MaxMoney;

	//UPROPERTY(VisibleAnywhere, Category = "Property")
	//TArray<UEffect*> Effects;

public:	
	// Sets default values for this component's properties
	UPropertyComponent();

	// Called when the game starts
	// TODO add save/load system
	virtual void BeginPlay() override;

	uint16 GetMana() const { return Mana; }
	uint16 GetMaxMana() const { return MaxMana; }

	uint16 GetStamina() const { return Stamina; }
	uint16 GetMaxStamina() const { return MaxStamina; }

	uint16 GetHealth() const { return Health; }
	uint16 GetMaxHealth() const { return MaxHealth; }

	uint16 GetMoney() const { return Money; }
	uint16 GetMaxMoney() const { return MaxMoney; }

	//TArray<UEffect*> GetEffects() const { return Effects; }
	
};
