// CC BY-NC 4.0

#pragma once

#include "Object.h"
#include "Consequence.h"
#include "Array.h"
#include "FrameworkAttribute.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeModify, UFrameworkAttribute*, Attribute);

/**
 * 
 */
UCLASS()
class FRAMEWORK_API UFrameworkAttribute : public UObject {

	GENERATED_BODY()

	//Should be deleted or changed to Destination?
	UPROPERTY(VisibleAnywhere, Category = "Property")
	FName Name;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	float BaseValue = 0;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	float Value;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	bool IsMinimumValueSet;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	bool IsMaximumValueSet;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	float MinimumValue;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	float MaximumValue;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	TArray<FModifier> Modifiers;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Property")
	FName GetName() const { return Name; }

	UFUNCTION(BlueprintCallable, Category = "Property")
	float GetValue() { return Value; }

	UFUNCTION(BlueprintCallable, Category = "Property")
	float GetBaseValue() { return BaseValue; }

	UFUNCTION(BlueprintCallable, Category = "Property")
	void SetBaseValue(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Property")
	void SetMinimumValue(float Minimal);

	UFUNCTION(BlueprintCallable, Category = "Property")
	void SetMaximumValue(float Maximum);

	UFUNCTION(BlueprintCallable, Category = "Property")
	void SetName(FName NewName) { Name = NewName; }
	
	UFUNCTION(BlueprintCallable, Category = "Property")
	void AddModifier(FModifier& Modifier);

	UFUNCTION(BlueprintCallable, Category = "Property")
	void RemoveModifier(FModifier& Modifier);

	UFUNCTION(BlueprintCallable, Category = "Property")
	void ClearModifiers();

	UFUNCTION(BlueprintCallable, Category = "Property")
	TArray<FModifier> GetModifiers() { return Modifiers; }

	UFUNCTION(Category = "Property")
	void Update();
};
