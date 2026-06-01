// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilitySystem/CombatGameplayAbility.h"

#include "AbilitySystem/CombatGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "Characters/GASCharacterBase.h"

UCombatGameplayAbility::UCombatGameplayAbility()
{
}

AGASCharacterBase* UCombatGameplayAbility::GetCombatCharacterFromActorInfo() const
{
	const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		return nullptr;
	}

	return Cast<AGASCharacterBase>(ActorInfo->AvatarActor.Get());
}

UAbilitySystemComponent* UCombatGameplayAbility::GetCombatAbilitySystemComponentFromActorInfo() const
{
	const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();
	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
	{
		return nullptr;
	}

	return ActorInfo->AbilitySystemComponent.Get();
}

bool UCombatGameplayAbility::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
	{
		return false;
	}

	const UAbilitySystemComponent* AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get();
	if (!AbilitySystemComponent)
	{
		return false;
	}

	return !AbilitySystemComponent->HasMatchingGameplayTag(FCombatGameplayTags::Get().State_Dead);
}
