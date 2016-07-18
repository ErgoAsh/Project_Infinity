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
	UPROPERTY(VisibleAnywhere, Category = "Properties")
	FName Name;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	float BaseValue = 0;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	float Value;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	bool bIsMinimumValueSet;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	bool bIsMaximumValueSet;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	float MinimumValue;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	float MaximumValue;

	UPROPERTY(VisibleAnywhere, Category = "PropPropertieserty")
	TArray<FModifier> Modifiers;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Properties")
	FName GetName() const { return Name; }

	UFUNCTION(BlueprintCallable, Category = "Properties")
	float GetValue() { return Value; }

	UFUNCTION(BlueprintCallable, Category = "Properties")
	float GetBaseValue() { return BaseValue; }

	UFUNCTION(BlueprintCallable, Category = "Properties")
	void SetBaseValue(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Properties")
	void SetMinimumValue(float Minimal);

	UFUNCTION(BlueprintCallable, Category = "Properties")
	void SetMaximumValue(float Maximum);

	UFUNCTION(BlueprintCallable, Category = "Properties")
	void SetName(FName& NewName) { Name = NewName; }
	
	UFUNCTION(BlueprintCallable, Category = "Properties")
	void AddModifier(FModifier& Modifier);

	UFUNCTION(BlueprintCallable, Category = "Properties")
	bool AddIfNotExist(FModifier& Modifier);

	UFUNCTION(BlueprintCallable, Category = "Properties")
	void RemoveModifier(FModifier& Modifier);

	UFUNCTION(BlueprintCallable, Category = "Properties")
	void ClearModifiers();

	UFUNCTION(BlueprintCallable, Category = "Properties")
	TArray<FModifier> GetModifiers() { return Modifiers; }

	UFUNCTION(Category = "Properties")
	void Update();
};
