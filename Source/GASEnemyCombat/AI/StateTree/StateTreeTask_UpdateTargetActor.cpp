// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI/StateTree/StateTreeTask_UpdateTargetActor.h"

#include "AI/GASEnemyAIController.h"
#include "StateTreeExecutionContext.h"

FStateTreeTask_UpdateTargetActor::FStateTreeTask_UpdateTargetActor()
{
#if WITH_EDITORONLY_DATA
	bConsideredForCompletion = false;
#endif
	bShouldCallTick = true;
}

EStateTreeRunStatus FStateTreeTask_UpdateTargetActor::EnterState(
	FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	UpdateTargetActor(Context);
	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FStateTreeTask_UpdateTargetActor::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	UpdateTargetActor(Context);
	return EStateTreeRunStatus::Running;
}

void FStateTreeTask_UpdateTargetActor::UpdateTargetActor(FStateTreeExecutionContext& Context) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	AGASEnemyAIController* EnemyAIController = Cast<AGASEnemyAIController>(InstanceData.AIController);
	AActor* ControllerTarget = EnemyAIController ? EnemyAIController->GetCurrentTargetActor() : nullptr;
	InstanceData.TargetActor = ControllerTarget;

	UE_LOG(LogTemp, Warning, TEXT("Controller Target = %s"), *GetNameSafe(ControllerTarget));
	UE_LOG(LogTemp, Warning, TEXT("StateTree TargetActor = %s"), *GetNameSafe(InstanceData.TargetActor));
}
