// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tasks/StateTreeAITask.h"
#include "StateTreeTask_UpdateTargetActor.generated.h"

class AAIController;
class AActor;

USTRUCT()
struct FStateTreeTask_UpdateTargetActorInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	AAIController* AIController = nullptr;

	UPROPERTY(EditAnywhere, Category = Output)
	AActor* TargetActor = nullptr;
};

/**
 * Global StateTree task that publishes the current perceived target actor.
 */
USTRUCT(meta = (DisplayName = "Update Target Actor", Category = "AI"))
struct GASENEMYCOMBAT_API FStateTreeTask_UpdateTargetActor : public FStateTreeAITaskBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeTask_UpdateTargetActorInstanceData;

	FStateTreeTask_UpdateTargetActor();

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;

private:
	void UpdateTargetActor(FStateTreeExecutionContext& Context) const;
};
