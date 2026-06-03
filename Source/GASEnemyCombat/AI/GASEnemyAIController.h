// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "GASEnemyAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UBehaviorTree;

/**
 * AIController for GAS enemies with sight perception.
 */
UCLASS()
class GASENEMYCOMBAT_API AGASEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AGASEnemyAIController();

	static const FName TargetActorKeyName;

	UFUNCTION(BlueprintPure, Category = "AI")
	AActor* GetCurrentTargetActor() const;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI")
	TObjectPtr<AActor> CurrentTargetActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	UFUNCTION()
	void HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
