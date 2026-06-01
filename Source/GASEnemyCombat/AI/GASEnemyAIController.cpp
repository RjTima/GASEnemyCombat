// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI/GASEnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

const FName AGASEnemyAIController::TargetActorKeyName(TEXT("TargetActor"));

AGASEnemyAIController::AGASEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig && AIPerceptionComponent)
	{
		SightConfig->SightRadius = 1500.0f;
		SightConfig->LoseSightRadius = 1800.0f;
		SightConfig->PeripheralVisionAngleDegrees = 70.0f;
		SightConfig->SetMaxAge(3.0f);
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		AIPerceptionComponent->ConfigureSense(*SightConfig);
		AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	}
}

void AGASEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIPerceptionComponent)
	{
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(
			this,
			&AGASEnemyAIController::OnTargetPerceptionUpdated);
	}
}

void AGASEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
}

void AGASEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor)
	{
		return;
	}

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		BlackboardComponent->SetValueAsObject(TargetActorKeyName, Actor);
		UE_LOG(LogTemp, Warning, TEXT("%s saw %s"), *GetNameSafe(this), *GetNameSafe(Actor));
		return;
	}

	UObject* CurrentTarget = BlackboardComponent->GetValueAsObject(TargetActorKeyName);
	if (CurrentTarget == Actor)
	{
		BlackboardComponent->ClearValue(TargetActorKeyName);
		UE_LOG(LogTemp, Warning, TEXT("%s lost %s"), *GetNameSafe(this), *GetNameSafe(Actor));
	}
}
