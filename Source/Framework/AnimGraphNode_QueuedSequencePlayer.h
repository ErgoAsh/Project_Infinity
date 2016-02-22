// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AnimGraphNode_Base.h"
#include "AnimGraphDefinitions.h"
#include "Kismet2/BlueprintEditorUtils.h"

//#include "Editor/AnimGraph/Classes/AnimGraphNode_Base.h"
#include "AnimNode_QueuedSequencePlayer.h"
#include "AnimGraphNode_QueuedSequencePlayer.generated.h"

UCLASS(MinimalAPI)
class UAnimGraphNode_QueuedSequencePlayer : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category=Settings)
	FAnimNode_QueuedSequencePlayer Node;

	// UEdGraphNode interface
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FString GetTooltip() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	// End of UEdGraphNode interface

private:
};
