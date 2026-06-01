// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI/BTTask_ActivateAbilityByTag.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTask_ActivateAbilityByTag::UBTTask_ActivateAbilityByTag()
{
	NodeName = TEXT("Activate Ability By Tag");
}

EBTNodeResult::Type UBTTask_ActivateAbilityByTag::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	UAbilitySystemComponent* AbilitySystemComponent =
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ControlledPawn);
	if (!AbilitySystemComponent)
	{
		return EBTNodeResult::Failed;
	}

	if (!AbilityTag.IsValid())
	{
		return EBTNodeResult::Failed;
	}

	FGameplayTagContainer AbilityTags;
	AbilityTags.AddTag(AbilityTag);

	const bool bActivated = AbilitySystemComponent->TryActivateAbilitiesByTag(AbilityTags);
	return bActivated ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
