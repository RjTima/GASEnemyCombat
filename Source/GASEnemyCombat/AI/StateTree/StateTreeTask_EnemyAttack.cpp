// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI/StateTree/StateTreeTask_EnemyAttack.h"

#include "Characters/GASEnemyCharacter.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FStateTreeTask_EnemyAttack::EnterState(
	FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	if (!InstanceData.Actor)
	{
		return EStateTreeRunStatus::Failed;
	}

	AGASEnemyCharacter* Enemy = Cast<AGASEnemyCharacter>(InstanceData.Actor);
	if (!Enemy)
	{
		return EStateTreeRunStatus::Failed;
	}

	Enemy->TryActivateAttackAbility();
	return EStateTreeRunStatus::Succeeded;
}
