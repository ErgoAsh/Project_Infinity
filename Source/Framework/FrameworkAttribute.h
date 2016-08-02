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
UCLASS(BlueprintType) //TODO add template?
class FRAMEWORK_API UFrameworkAttribute : public UObject {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	FName Type;

	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	float BaseValue = 0;

	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	float Value;

	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	bool bIsMinimumValueSet;

	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	bool bIsMaximumValueSet;

	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	float MinimumValue;

	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	float MaximumValue;

	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	TArray<FModifier> Modifiers;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	FName GetType() const { return Type; }

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetValue() const { return Value; }

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetBaseValue() const { return BaseValue; }

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetBaseValue(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetMinimumValue(float Minimal);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetMaximumValue(float Maximum);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetType(FName& NewType) { Type = NewType; }
	
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void AddModifier(FModifier& Modifier);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	bool AddIfNotExist(FModifier& Modifier); //TODO delete/refactor

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void RemoveModifier(FModifier& Modifier);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void ClearModifiers();

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	TArray<FModifier> GetModifiers() { return Modifiers; }

	UFUNCTION(Category = "Attribute")
	void Update();
};
