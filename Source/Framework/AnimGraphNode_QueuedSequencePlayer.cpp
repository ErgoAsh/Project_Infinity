// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Framework.h"
#include "AnimGraphNode_QueuedSequencePlayer.h"

// #include "Editor/BlueprintGraph/Classes/EdGraphSchema_K2_Actions.h"
//#include "Editor/GraphEditor/Public/GraphEditorActions.h"
//#include "Editor/AnimGraph/Classes/AnimationGraphSchema.h"
//#include "CompilerResultsLog.h"
//#include "AssetRegistryModule.h"


/////////////////////////////////////////////////////
// UAnimGraphNode_QueuedSequencePlayer

UAnimGraphNode_QueuedSequencePlayer::UAnimGraphNode_QueuedSequencePlayer(const FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

FLinearColor UAnimGraphNode_QueuedSequencePlayer::GetNodeTitleColor() const
{
	if ((Node.CurrentSequence != NULL) && Node.CurrentSequence->IsValidAdditive())
	{
		return FLinearColor(0.10f, 0.60f, 0.12f);
	}
	else
	{
		return FColor(200, 100, 100);
	}
}

FString UAnimGraphNode_QueuedSequencePlayer::GetTooltip() const
{
	return TEXT("Tooltip lol");
}

FText UAnimGraphNode_QueuedSequencePlayer::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("QueuedSequencePlayer"));
}
