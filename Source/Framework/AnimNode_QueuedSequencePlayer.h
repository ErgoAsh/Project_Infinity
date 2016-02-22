// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Animation/AnimNodeBase.h"
#include "AnimNode_QueuedSequencePlayer.generated.h"

#pragma once

// Sequence player node
USTRUCT()
struct FAnimNode_QueuedSequencePlayer : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()
public:
	// The animation sequence asset to play
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AlwaysAsPin))
	UAnimSequenceBase* NextSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FName EndOfPlayEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float EndOfPlayEventTime;

	// The internal time accumulator (position within the animation asset being played)
	UPROPERTY(BlueprintReadWrite, Transient, Category=DoNotEdit)
	float InternalTimeAccumulator;

	UPROPERTY(transient)
	UAnimSequenceBase* CurrentSequence;

	UPROPERTY(transient)
	float LastInternalTimeAccumulator;


public:	
	FAnimNode_QueuedSequencePlayer()
		: CurrentSequence(NULL)
		, NextSequence(nullptr)
		, InternalTimeAccumulator(0.0f)
		, LastInternalTimeAccumulator(0.0f)
	{
	}

	// FAnimNode_Base interface
	GAME_API virtual void Initialize(const FAnimationInitializeContext& Context) override;
	GAME_API virtual void CacheBones(const FAnimationCacheBonesContext & Context) override;
	GAME_API virtual void Update(const FAnimationUpdateContext& Context) override;
	GAME_API virtual void Evaluate(FPoseContext& Output) override;
	// GAME_API virtual void OverrideAsset(UAnimationAsset* NewAsset) override;
	GAME_API virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	// End of FAnimNode_Base interface
};
