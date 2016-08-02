// CC BY-NC 4.0

#include "Framework.h"
#include "DefenseComponent.h"


UDefenseComponent::UDefenseComponent() {
	Dark = NewObject<UFrameworkAttribute>();
	Dark->SetMaximumValue(100);
	Dark->SetMinimumValue(-100);
	Ice = NewObject<UFrameworkAttribute>();
	Ice->SetMaximumValue(100);
	Ice->SetMinimumValue(-100);
	Lightning = NewObject<UFrameworkAttribute>();
	Lightning->SetMaximumValue(100);
	Lightning->SetMinimumValue(-100);
	Magic = NewObject<UFrameworkAttribute>();
	Magic->SetMaximumValue(100);
	Magic->SetMinimumValue(-100);
	Fire = NewObject<UFrameworkAttribute>();
	Fire->SetMaximumValue(100);
	Fire->SetMinimumValue(-100);
	Mind = NewObject<UFrameworkAttribute>();
	Mind->SetMaximumValue(100);
	Mind->SetMinimumValue(-100);

	Slash = NewObject<UFrameworkAttribute>();
	Slash->SetMaximumValue(100);
	Slash->SetMinimumValue(-100);
	Pierce = NewObject<UFrameworkAttribute>();
	Pierce->SetMaximumValue(100);
	Pierce->SetMinimumValue(-100);
	Blunt = NewObject<UFrameworkAttribute>();
	Blunt->SetMaximumValue(100);
	Blunt->SetMinimumValue(-100);

	Poise = NewObject<UFrameworkAttribute>();
	Poise->SetMaximumValue(100);
	Poise->SetMinimumValue(-100);
	Speed = NewObject<UFrameworkAttribute>();
	Speed->SetMaximumValue(300);
	Speed->SetMinimumValue(0);
	Speed->SetBaseValue(100);
}

void UDefenseComponent::ClearModifiers() {
	Dark->ClearModifiers();
	Lightning->ClearModifiers();
	Ice->ClearModifiers();
	Magic->ClearModifiers();
	Fire->ClearModifiers();
	Mind->ClearModifiers();

	Slash->ClearModifiers();
	Pierce->ClearModifiers();
	Blunt->ClearModifiers();

	Poise->ClearModifiers();
	Speed->ClearModifiers();
}

