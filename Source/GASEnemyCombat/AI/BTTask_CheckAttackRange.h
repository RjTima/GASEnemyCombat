// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BTTask_CheckAttackRange.generated.h"

/**
 * Behavior Tree task that checks whether the controlled pawn is in attack range of a target actor.
 */
UCLASS()
class GASENEMYCOMBAT_API UBTTask_CheckAttackRange : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_CheckAttackRange();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRange = 200.0f;
};
