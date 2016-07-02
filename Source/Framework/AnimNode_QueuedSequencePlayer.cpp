// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Framework.h"
#include "AnimInstanceProxy.h"
#include "AnimNode_QueuedSequencePlayer.h"

/////////////////////////////////////////////////////
// FAnimSequencePlayerNode

void FAnimNode_QueuedSequencePlayer::Initialize(const FAnimationInitializeContext& Context)
{
	EvaluateGraphExposedInputs.Execute(Context);
	InternalTimeAccumulator = 0.0f;
}

void FAnimNode_QueuedSequencePlayer::CacheBones(const FAnimationCacheBonesContext & Context) 
{
}

void FAnimNode_QueuedSequencePlayer::Update(const FAnimationUpdateContext& Context)
{
	EvaluateGraphExposedInputs.Execute(Context);

	if (CurrentSequence == nullptr ||
	   (NextSequence != nullptr && (InternalTimeAccumulator + SMALL_NUMBER >= CurrentSequence->SequenceLength || LastInternalTimeAccumulator > InternalTimeAccumulator)))
	{
		CurrentSequence = NextSequence;
		InternalTimeAccumulator = 0;
	}

	if ((CurrentSequence != NULL) && (Context.AnimInstanceProxy->GetSkeleton()->IsCompatible(CurrentSequence->GetSkeleton())))
	{
		const float fTriggerTime = FMath::Max(0.f, CurrentSequence->SequenceLength - EndOfPlayEventTime);
		if (LastInternalTimeAccumulator < fTriggerTime && InternalTimeAccumulator >= fTriggerTime)
		{
			UAnimInstance* Instance = Context.AnimInstanceProxy->GetSkelMeshComponent()->GetAnimInstance();
			UFunction* EOPFunc = Instance->FindFunction(EndOfPlayEvent);
			if (EOPFunc != nullptr)
			{
				Instance->ProcessEvent(EOPFunc, nullptr);
			}
		}

		const float FinalBlendWeight = Context.GetFinalBlendWeight();

		// Create a tick record and fill it out
		UAnimInstance* Instance = Context.AnimInstanceProxy->GetSkelMeshComponent()->GetAnimInstance();
		FAnimGroupInstance* SyncGroup;
		FAnimTickRecord& TickRecord = Context.AnimInstanceProxy->CreateUninitializedTickRecord(INDEX_NONE, /*out*/ SyncGroup);

		Context.AnimInstanceProxy->MakeSequenceTickRecord(TickRecord, CurrentSequence, false, 1.0, FinalBlendWeight, /*inout*/ InternalTimeAccumulator, *TickRecord.MarkerTickRecord);
	}

	LastInternalTimeAccumulator = InternalTimeAccumulator;
}

//void FAnimNode_QueuedSequencePlayer::Evaluate(FPoseContext& Output)
//{
//	if ((CurrentSequence != NULL) && (Output.AnimInstanceProxy->GetSkeleton()->IsCompatible(CurrentSequence->GetSkeleton())))
//	{
//		UAnimInstance* Instance = Output.AnimInstanceProxy->GetSkelMeshComponent()->GetAnimInstance();
//		Instance->ParallelEvaluateAnimation(false, Output.AnimInstanceProxy->GetSkelMeshComponent()->SkeletalMesh, Atoms, Output.Curve );
//		//Output.AnimInstance->SequenceEvaluatePose(CurrentSequence, Output.Pose, FAnimExtractContext(InternalTimeAccumulator, false));
//	}
//	else
//	{
//		Output.ResetToRefPose();
//	}
//}

void FAnimNode_QueuedSequencePlayer::GatherDebugData(FNodeDebugData& DebugData)
{
	//FString DebugLine = DebugData.GetNodeName(this);
	//
	//DebugLine += FString::Printf(TEXT("('%s' Play Time: %.3f)"), *Sequence->GetName(), InternalTimeAccumulator);
	//DebugData.AddDebugItem(DebugLine, true);
}