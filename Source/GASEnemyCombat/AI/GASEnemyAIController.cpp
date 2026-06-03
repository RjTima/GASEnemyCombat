// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI/GASEnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Pawn.h"
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
			&AGASEnemyAIController::HandleTargetPerceptionUpdated);
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

AActor* AGASEnemyAIController::GetCurrentTargetActor() const
{
	return CurrentTargetActor;
}

void AGASEnemyAIController::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor)
	{
		return;
	}

	if (Actor == GetPawn())
	{
		return;
	}

	APawn* SensedPawn = Cast<APawn>(Actor);
	if (!SensedPawn || !SensedPawn->IsPlayerControlled())
	{
		return;
	}

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (Stimulus.WasSuccessfullySensed())
	{
		CurrentTargetActor = Actor;

		if (BlackboardComponent)
		{
			BlackboardComponent->SetValueAsObject(TargetActorKeyName, Actor);
		}

		UE_LOG(LogTemp, Warning, TEXT("AI Target Set = %s"), *GetNameSafe(Actor));
		return;
	}

	if (CurrentTargetActor == Actor)
	{
		CurrentTargetActor = nullptr;

		if (BlackboardComponent)
		{
			BlackboardComponent->ClearValue(TargetActorKeyName);
		}

		UE_LOG(LogTemp, Warning, TEXT("AI Target Cleared = %s"), *GetNameSafe(Actor));
	}
}
