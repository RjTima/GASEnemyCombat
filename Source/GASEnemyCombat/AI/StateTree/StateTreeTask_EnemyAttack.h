// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tasks/StateTreeAITask.h"
#include "StateTreeTask_EnemyAttack.generated.h"

class AActor;

USTRUCT()
struct FStateTreeTask_EnemyAttackInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	AActor* Actor = nullptr;
};

/**
 * StateTree task that asks a GAS enemy character to activate its attack ability.
 */
USTRUCT(meta = (DisplayName = "Enemy Attack", Category = "AI|Combat"))
struct GASENEMYCOMBAT_API FStateTreeTask_EnemyAttack : public FStateTreeAITaskBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeTask_EnemyAttackInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};
