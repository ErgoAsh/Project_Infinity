// CC BY-NC 4.0

#include "Framework.h"
#include "Consequence.h"
#include "FrameworkAttribute.h"

void UFrameworkAttribute::AddModifier(FModifier& Modifier) {
	Modifiers.Add(Modifier);
	Update();
}

bool UFrameworkAttribute::AddIfNotExist(FModifier& Modifier) {
	if (!Modifiers.Contains(Modifier)) {
		Modifiers.Add(Modifier);
		Update();
		return true;
	}
	return false;
}

void UFrameworkAttribute::RemoveModifier(FModifier& Modifier) {
	Modifiers.Remove(Modifier);
	Update();
}

void UFrameworkAttribute::SetBaseValue(float NewValue) {
	BaseValue = NewValue;
	Update();
}

void UFrameworkAttribute::SetMinimumValue(float Minimum) {
	bIsMinimumValueSet = true;
	MinimumValue = Minimum;
}

void UFrameworkAttribute::SetMaximumValue(float Maximum) {
	bIsMaximumValueSet = true;
	MaximumValue = Maximum;
}

void UFrameworkAttribute::ClearModifiers() {
	Modifiers.Empty();
	Update();
}

void UFrameworkAttribute::Update() {
	Value = BaseValue;
	for (int32 i = 0; i < Modifiers.Num(); i++) {
		switch (Modifiers[i].Type.GetValue()) {
		case EModifyType::Add:
			Value += Modifiers[i].AmountModified;
		case EModifyType::Remove:
			Value -= Modifiers[i].AmountModified;
		case EModifyType::Divide:
			Value /= Modifiers[i].AmountModified;
		case EModifyType::Multiply:
			Value *= Modifiers[i].AmountModified;
		case EModifyType::AddPercentage:
			Value += (Modifiers[i].AmountModified / Value) * 100;
		case EModifyType::RemovePercentage:
			Value -= (Modifiers[i].AmountModified / Value) * 100;
		default:
			break;
		}

		if (bIsMinimumValueSet && Value < MinimumValue) Value = MinimumValue;
		if (bIsMaximumValueSet && Value > MaximumValue) Value = MaximumValue;
	}
}