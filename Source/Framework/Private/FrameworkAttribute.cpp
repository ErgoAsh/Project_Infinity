// CC BY-NC 4.0

#include "Framework.h"
#include "Consequence.h"
#include "FrameworkAttribute.h"

void UFrameworkAttribute::AddModifier(FModifier& Modifier) {
	Modifiers.Add(Modifier);
	Update();
}

void UFrameworkAttribute::RemoveModifier(FModifier& Modifier) {
	Modifiers.Remove(Modifier);
	Update();
}

void UFrameworkAttribute::SetBaseValue(float NewValue) {
	BaseValue = NewValue;
	Update();
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
	}
}
